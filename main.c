#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>

#include <math.h>
#include "shader.h"
#include "debug.h"

#define WIDTH 900
#define HEIGHT 600

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

	// enable debug output - MessageCallback from debug.h
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	
	// vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer
	
	float vertices[] = {
		-1.0f,  1.0f, 1.0f, 0.0f, 0.0f, // Top-left
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
		-1.0f, -1.0f, 1.0f, 1.0f, 1.0f  // Bottom-left
	};
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	// vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	GLuint ebo;
	glGenBuffers(1, &ebo);
	
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// createShaderProgram defined in shader.h
	GLuint shaderProgram = createShaderProgram("test.vsh", "test.fsh");
	
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	
	// link and use the shader program
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);
	
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
		
	outError();
	
	bool running = true;
	while(running){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_EVENT_QUIT:
					running = false; break;
			}
		}
		
		// draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(window);
		
		
	}
	
	// Cleanup
	SDL_GL_DestroyContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}