#include "shader.h"

GLuint shaderCreate (const GLchar* source, GLenum shaderType){
    GLuint shader;
    shader = glCreateShader (shaderType);
    glShaderSource (shader, 1, &source, NULL);
    glCompileShader (shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv (shader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog (shader, 512, NULL, infoLog);
        fprintf (stderr, "Shader compilation failed:\n%s\n", infoLog);
    }

    return shader;
}

GLuint shaderLink (GLuint* shaders){
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    int numShaders = sizeof (shaders) / sizeof (shaders[0]);
    for (int i = 0; i < numShaders; i++)
        glAttachShader (shaderProgram, shaders[i]);
    
    glLinkProgram (shaderProgram);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv (shaderProgram, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog (shaderProgram, 512, NULL, infoLog);
        fprintf (stderr, "Shader program linking failed:\n%s\n", infoLog);
    }

    for (int i = 0; i < numShaders; i++)
        glDeleteShader (shaders[i]);

    return shaderProgram;
}
