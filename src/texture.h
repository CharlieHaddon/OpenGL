#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <SOIL/SOIL.h>

GLuint textureCreate(GLchar* name, GLchar* imagePath, GLenum textureUnit, 
        GLuint shaderProgram);

#endif
