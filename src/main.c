#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>

#include "flow.h"
#include "shader.h"
#include "file.h"
#include "texture.h"
#include "linear.h"
#include "transform.h"

const int WIDTH = 800;
const int HEIGHT = 600;

const double pi = 4 * atan (1);

void keyCallback (GLFWwindow* window, int key, int scancode, 
        int action, int mode){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose (window, GL_TRUE);
}

int main (){
    /* Initialisation */
    GLFWwindow* window = flowInit (WIDTH, HEIGHT, "OpenGL");
    glfwSetKeyCallback (window, keyCallback);

    /* Vertex data */
    GLfloat vertices[] = {
         /* Positions */      /* Colours */       /* Texture coordinates */
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    GLuint elements[] = {
        0, 1, 3,
        1, 2, 3
    };

    /* Create shaders */
    const GLchar* vertexShaderSource;
    vertexShaderSource = fileRead ("shaders/vertex-shader.glsl");
    const GLchar* fragmentShaderSource;
    fragmentShaderSource = fileRead ("shaders/fragment-shader.glsl");

    GLuint vertexShader; 
    vertexShader = shaderCreate (vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader;
    fragmentShader = shaderCreate (fragmentShaderSource, GL_FRAGMENT_SHADER);

    GLuint shaders[] = {vertexShader, fragmentShader};
    GLuint shaderProgram = shaderLink (shaders);

    /* Generate data storage buffers */
    GLuint VAO;
    glGenVertexArrays (1, &VAO);
    GLuint VBO;
    glGenBuffers (1, &VBO);
    GLuint EBO;
    glGenBuffers (1, &EBO);

    /* Store information on specific vertex array for redrawing */
    glBindVertexArray (VAO);
    /* Buffer vertices */
    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, 
            GL_STATIC_DRAW);
    /* Buffer elements */
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (elements), elements,
            GL_STATIC_DRAW);
    /* Position */
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat), 
            (GLvoid*)0);
    glEnableVertexAttribArray (0);
    /* Colour */
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
            (GLvoid*)(3 * sizeof (GLfloat)));
    glEnableVertexAttribArray (1);
    /* Texture coordinates */
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
            (GLvoid*)(6 * sizeof (GLfloat)));
    glEnableVertexAttribArray (2);
    /* Unbind vertex array */
    glBindVertexArray (0);

    /* Create texture */
    GLuint texture;
    texture = textureCreate ("uniTexture", "images/container.jpg", 0, 
            shaderProgram);

    /* Matrices */
    vec3 axis = {1.0f, 0.0f, 0.0f};
    mat4 model = mat4Rotate (axis, -(pi / 4));

    vec3 translation = {0.0f, 0.0f, 5.0f};
    mat4 view = mat4Translate (translation);

    mat4 projection = mat4Perspective (pi / 2, (3 * pi) / 8, 0.1f, 100.0f);
    
    GLint modelLoc = glGetUniformLocation (shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation (shaderProgram, "view");
    GLint projLoc = glGetUniformLocation (shaderProgram, "projection");

    GLfloat modelArray[16];
    mat4ToArray (model, modelArray);
    GLfloat viewArray[16];
    mat4ToArray (view, viewArray);
    GLfloat projArray[16];
    mat4ToArray (projection, projArray);

    printf ("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
            projArray[0], projArray[1], projArray[2], projArray[3],
            projArray[4], projArray[5], projArray[6], projArray[7],
            projArray[8], projArray[9], projArray[10], projArray[11],
            projArray[12], projArray[13], projArray[14], projArray[15]);

    /* Render code executed in main loop */
    int renderFrame (){
        glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT);

        glActiveTexture (GL_TEXTURE0);
        glBindTexture (GL_TEXTURE_2D, texture);
        glUseProgram (shaderProgram);

        glUniformMatrix4fv (modelLoc, 1, GL_FALSE, modelArray);
        glUniformMatrix4fv (viewLoc, 1, GL_FALSE, viewArray);
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, projArray);

        glBindVertexArray (VAO);
        glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray (0);

        return 0; 
    }

    /* Main loop */
    flowMain (window, &renderFrame);

    /* Cleanly exit */
    flowExit ();
    return 0;
}
