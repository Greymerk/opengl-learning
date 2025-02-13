#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>

#include <math.h>
#include <sys/time.h>
#include "shader.h"

#define WIDTH 900
#define HEIGHT 600

double sinceEpoch();
void outError();

// https://open.gl/drawing
int main( int argc, const char* argv[] ) {
	
	//Start SDL
	SDL_Init(SDL_INIT_VIDEO);
	
	// Set up OpenGL 3.2 context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	
	// Create window 
	SDL_Window* window = SDL_CreateWindow("Hello OpenGL", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	
	// Create OpenGL Context
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	
	float vertices[] = {
		0.0f,  0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};
	
	// vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// createShaderProgram defined in shader.h
	GLuint shaderProgram = createShaderProgram("test.vsh", "test.fsh");
	
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	
	// link and use the shader program
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);
	
	// set triangle color to red
	GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
		
	outError();
	
	double start = sinceEpoch();
	
	bool running = true;
	while(running){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_EVENT_QUIT:
					running = false; break;
			}
		}
		
		double now = sinceEpoch();
		double duration = (now - start);
		
		glUniform3f(uniColor, (sin(duration * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
		
		// draw
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SDL_GL_SwapWindow(window);
		
	}
	
	// Cleanup
	SDL_GL_DestroyContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void outError(){
	switch(glGetError()){
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			printf("Invalid Enum\n"); break;
		case GL_INVALID_VALUE:
			printf("Invalid Value\n"); break;
		case GL_INVALID_OPERATION:
			printf("Invalid Operation\n"); break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printf("Invalid Framebuffer Operation\n"); break;
		case GL_OUT_OF_MEMORY:
			printf("Out of memory\n"); break;
		case GL_STACK_UNDERFLOW:
			printf("Stack underflow\n"); break;
		case GL_STACK_OVERFLOW:
			printf("Stack underflow\n"); break;		
	}
}

double sinceEpoch(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time_t seconds = tv.tv_sec;
	useconds_t micros = tv.tv_usec;
	
	double time = seconds + micros / 1e6;
	return time;
}