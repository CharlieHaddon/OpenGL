#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "flow.h"
#include "shader.h"
#include "file.h"
#include "texture.h"
#include "linear.h"
#include "transform.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;
bool keys[1024];

const double pi = 4 * atan (1);

/* Camera */
vec3 up = {0.0f, 1.0f, 0.0f};
vec3 cameraPosition = {0.0f, 0.0f, 3.0f};
vec3 cameraForward = {0.0f, 0.0f, -1.0f};

void keyCallback (GLFWwindow* window, int key, int scancode, 
        int action, int mode){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose (window, GL_TRUE);

    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

float lastx, lasty;
float pitch, yaw;
bool firstMouse = true;
void mouseCallback (GLFWwindow* window, double xPos, double yPos){
    if (firstMouse){
        lastx = xPos;
        lasty = yPos;
        firstMouse = false;
    }
    float xOffset = xPos - lastx;
    float yOffset = lasty - yPos;
    lastx = xPos;
    lasty = yPos;

    float sensitivity = 0.20f * timeDelta;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > (pi / 2) - 0.01f)
        pitch = (pi / 2) - 0.01f;
    if (pitch < -(pi / 2) + 0.01f)
        pitch = -(pi / 2) + 0.01f;
}

int gameUpdate (){
    float cameraSpeed = 3.0f * timeDelta;
    if (keys[GLFW_KEY_W])
        cameraPosition = vec3Add (cameraPosition, 
                vec3Scale (cameraSpeed, cameraForward));
    if (keys[GLFW_KEY_S])
        cameraPosition = vec3Add (cameraPosition, 
                vec3Scale (-cameraSpeed, cameraForward));
    if (keys[GLFW_KEY_D])
        cameraPosition = vec3Add (cameraPosition, 
                vec3Scale (cameraSpeed, vec3Norm 
                    (vec3Cross (cameraForward, up))));
    if (keys[GLFW_KEY_A])
        cameraPosition = vec3Add (cameraPosition, 
                vec3Scale (-cameraSpeed, vec3Norm 
                    (vec3Cross (cameraForward, up))));

    vec3 forward;
    forward.x = cos (pitch) * sin (yaw);
    forward.y = sin (pitch);
    forward.z = -cos (pitch) * cos (yaw);

    cameraForward = vec3Norm (forward);

    return 0;
}

int main (){
    /* Initialisation */
    GLFWwindow* window = flowInit (WIDTH, HEIGHT, "OpenGL");
    glfwSetKeyCallback (window, keyCallback);
    glfwSetCursorPosCallback (window, mouseCallback);

    /* Vertex data */
    GLfloat vertices[] = {
         /* Positions */      /* Texture coordinates */
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    GLuint elements[] = {
    };

    vec3 cubePositions[] = {
        (vec3){0.0f, 0.0f, 0.0f},
        (vec3){2.0f, 2.0f, 0.0f},
        (vec3){-1.5f, -2.2f, -2.5f},
        (vec3){-3.8f, -2.0f, -12.3f},
        (vec3){2.4f, -0.4f, -3.5f},
        (vec3){-1.7f, 3.0f, -7.5f},
        (vec3){1.3f, -2.0f, -2.5f},
        (vec3){1.5f, 2.0f, -2.5f},
        (vec3){-1.3f, 1.0f, -1.5f}
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
        glBufferData (GL_ARRAY_BUFFER, 
                      sizeof (vertices), 
                      vertices, 
                      GL_STATIC_DRAW);

        /* Buffer elements */
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, 
                      sizeof (elements), 
                      elements,
                      GL_STATIC_DRAW);

        /* Position */
        glVertexAttribPointer (0, 
                               3, 
                               GL_FLOAT, 
                               GL_FALSE, 
                               5 * sizeof (GLfloat), 
                               (GLvoid*)0);
        glEnableVertexAttribArray (0);

        /* Texture coordinates */
        glVertexAttribPointer (1, 
                               2, 
                               GL_FLOAT, 
                               GL_FALSE, 
                               5 * sizeof (GLfloat),
                               (GLvoid*)(3 * sizeof (GLfloat)));
        glEnableVertexAttribArray (1);
    /* Unbind vertex array */
    glBindVertexArray (0);

    /* Create texture */
    GLuint texture;
    texture = textureCreate ("uniTexture", "images/container.jpg", 0, 
            shaderProgram);

    
    /* Matrices */
    mat4 model = (mat4){
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    mat4 projection = mat4Perspective (pi / 2, (float)WIDTH / (float)HEIGHT, 
                                       0.01f, 100.0f);
    
    GLint modelLoc = glGetUniformLocation (shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation (shaderProgram, "view");
    GLint projLoc = glGetUniformLocation (shaderProgram, "projection");

    GLfloat modelArray[16];
    mat4ToArray (model, modelArray);
    GLfloat viewArray[16]; 
    GLfloat projArray[16];
    mat4ToArray (projection, projArray);

    /* Render code executed in main loop */
    int renderUpdate (){
        glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture (GL_TEXTURE0);
        glBindTexture (GL_TEXTURE_2D, texture);
        glUseProgram (shaderProgram);

        mat4 view = mat4LookAt (cameraPosition, 
                vec3Add (cameraPosition, cameraForward), up);
        mat4ToArray (view, viewArray);

        glUniformMatrix4fv (viewLoc, 1, GL_FALSE, viewArray);
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, projArray);

        glBindVertexArray (VAO);
        for (int i = 0; i < 9; i++){
            mat4 model = (mat4){
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
            vec3 axis = {1.0f, 0.3f, 0.5f};
            float angle = 10 * i;

            model = mat4Mult (mat4Rotate (axis, angle), model);
            model = mat4Mult (mat4Translate (cubePositions[i]), model);

            mat4ToArray (model, modelArray);
            glUniformMatrix4fv (modelLoc, 1, GL_FALSE, modelArray);

            glDrawArrays (GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray (0);

        return 0; 
    }

    /* Main loop */
    flowMain (window, &renderUpdate, &gameUpdate);

    /* Cleanly exit */
    flowExit ();
    return 0;
}


