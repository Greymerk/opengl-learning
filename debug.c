#include <stdio.h>
#include "debug.h"

#include <GL/glew.h>

void GLAPIENTRY MessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
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