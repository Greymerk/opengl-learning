#ifndef DEBUG_H
#define DEBUG_H

#include <GL/glew.h>

void GLAPIENTRY MessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam);

void outError();

#endif