#ifndef SHADER_H
#define SHADER_H

GLuint createShaderProgram(char* vertFile, char* fragFile);
char* readShaderSource(char* filename);
GLuint compileShader(const char* src, GLenum type);
bool isCompiled(GLuint shader);

#endif