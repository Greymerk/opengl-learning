#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>

#define COLOR_WHITE 0xffffffff

bool isCompiled(GLuint shader);
void outError();

// https://open.gl/drawing
int main( int argc, char* args[] ) {
	
	//Start SDL
	SDL_Init(SDL_INIT_VIDEO);
	
	// Set up OpenGL 3.2 context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	
	// Create window 
	SDL_Window* window = SDL_CreateWindow("Hello OpenGL", 900, 600, SDL_WINDOW_OPENGL);
	
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
	
	// define vertex and fragment shader source
	const char* vertSource = 	"#version 150 core\n"
								"in vec2 position;\n"
								"void main()\n"
								"{\n"
								"	gl_Position = vec4(position, 0.0, 1.0);\n"
								"}\0";
	
	const char* fragSource = 	"#version 150 core\n"
								"out vec4 outColor;\n"
								"void main()\n"
								"{\n"
								"	outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
								"}\0";

	// create shader objects
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSource, NULL);
	glCompileShader(vertexShader);
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, NULL);
	glCompileShader(fragmentShader);
	
	if(isCompiled(vertexShader)){
		printf("vertex compiled successfully\n");	
	} else {
		printf("vertex compiled unsuccessfully\n");	
	}
	
	if(isCompiled(vertexShader)){
		printf("fragment compiled successfully\n");	
	} else {
		printf("fragment compiled unsuccessfully\n");	
	}
	
	// create shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	
	// link and use the shader program
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	outError();
	glEnableVertexAttribArray(posAttrib);
	

	

	
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
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SDL_GL_SwapWindow(window);
	}
	
    // Cleanup
	SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

	return EXIT_SUCCESS;
}

bool isCompiled(GLuint shader){
	
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	
	if(isCompiled == GL_FALSE){
		return false;
	}
	
	return true;
}

void outError(){
	switch(glGetError()){
		case GL_NO_ERROR:
			printf("No Error\n");
			break;
		case GL_INVALID_ENUM:
			printf("Invalid Enum\n");
			break;
		case GL_INVALID_VALUE:
			printf("Invalid Value\n");
			break;
		case GL_INVALID_OPERATION:
			printf("Invalid Operation\n");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printf("Invalid Framebuffer Operation\n");
			break;
		case GL_OUT_OF_MEMORY:
			printf("Out of memory\n");
			break;
		case GL_STACK_UNDERFLOW:
			printf("Stack underflow\n");
			break;
		case GL_STACK_OVERFLOW:
			printf("Stack underflow\n");
			break;		
	}
}