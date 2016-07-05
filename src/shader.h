#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <stdio.h>

GLuint shaderCreate (const GLchar* source, GLenum shaderType);
GLuint shaderLink (GLuint* shaders);

#endif
