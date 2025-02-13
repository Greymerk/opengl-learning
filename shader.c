#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glew.h>
#include "shader.h"

bool isCompiled(GLuint shader);
GLuint compileShader(const char* src, GLenum type);
char* readShaderSource(char* filename);

GLuint createShaderProgram(char* vertFile, char* fragFile){
	// define vertex and fragment shader source
	const char* vertSource = readShaderSource(vertFile);
	const char* fragSource = readShaderSource(fragFile);

	// create shader objects
	GLuint vertexShader = compileShader(vertSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragSource, GL_FRAGMENT_SHADER);
	
	// create shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	
	return shaderProgram;
}

char* readShaderSource(char* filename){

	char* buffer = 0;
	long length;
	FILE* fp = fopen(filename, "rb");
	
	if(fp){
		fseek(fp, 0, SEEK_END);
		length = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		buffer = malloc(length);
		if(buffer){
			fread(buffer, 1, length, fp);
		}
		
		fclose(fp);
	}
	
	return buffer;
}

GLuint compileShader(const char* src, GLenum type){
	
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	
	if(!isCompiled(shader)){
		printf("Shader compilation failed: %d\n", type);	
	}
	
	return shader;
}

bool isCompiled(GLuint shader){
	
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	
	if(isCompiled == GL_FALSE){
		return false;
	}
	
	return true;
}