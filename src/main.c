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

GLFWwindow* window;
const int WIDTH = 800;
const int HEIGHT = 600;

const double pi = 4 * atan (1);

/* Camera */
vec3 up = {0.0f, 1.0f, 0.0f};
vec3 cameraPosition = {0.0f, 0.0f, 3.0f};
vec3 cameraForward = {0.0f, 0.0f, -1.0f};
vec3 lampPos = {2, 1.6, 1.4};

double pitch = 0;
double yaw = 0;

vec3 cubeColour = {1.0f, 0.5f, 0.31f};

int gameUpdate (){
    if (keyState[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose (window, true);

    float cameraSpeed = 3.0f * timeDelta;
    if (keyState[GLFW_KEY_W])
        cameraPosition = vec3Add (cameraPosition, 
                vec3Scale (cameraSpeed, cameraForward));
    if (keyState[GLFW_KEY_S])
        cameraPosition = vec3Add (cameraPosition, 
                vec3Scale (-cameraSpeed, cameraForward));
    if (keyState[GLFW_KEY_D])
        cameraPosition = vec3Add (cameraPosition, 
                vec3Scale (cameraSpeed, vec3Norm 
                    (vec3Cross (cameraForward, up))));
    if (keyState[GLFW_KEY_A])
        cameraPosition = vec3Add (cameraPosition, 
                vec3Scale (-cameraSpeed, vec3Norm 
                    (vec3Cross (cameraForward, up))));
    
    float mouseSpeed = 0.15 * timeDelta;

    yaw += mousexOffset * mouseSpeed;
    pitch += mouseyOffset * mouseSpeed;

    if (pitch > (pi / 2) - 0.01f)
        pitch = (pi / 2) - 0.01f;
    if (pitch < -(pi / 2) + 0.01f)
        pitch = -(pi / 2) + 0.01f;

    vec3 forward;
    forward.x = cos (pitch) * sin (yaw);
    forward.y = sin (pitch);
    forward.z = -cos (pitch) * cos (yaw);

    cameraForward = vec3Norm (forward);

    return 0;
}

int main (){
    /* Initialisation */
    window = flowInit (WIDTH, HEIGHT, "OpenGL");

    /* Vertex data */
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    /* Cube shader */
    const GLchar* cubeVertexShaderSource;
    cubeVertexShaderSource = fileRead ("shaders/vertex-shader.glsl");
    const GLchar* cubeFragmentShaderSource;
    cubeFragmentShaderSource = fileRead ("shaders/fragment-shader.glsl");

    GLuint cubeVertexShader; 
    cubeVertexShader = shaderCreate (cubeVertexShaderSource, 
            GL_VERTEX_SHADER);
    GLuint cubeFragmentShader;
    cubeFragmentShader = shaderCreate (cubeFragmentShaderSource, 
            GL_FRAGMENT_SHADER);

    GLuint shaders[] = {cubeVertexShader, cubeFragmentShader};
    GLuint cubeShaderProgram = shaderLink (shaders);
    
    /* Lamp shader */
    const GLchar* lampVertexShaderSource;
    lampVertexShaderSource = fileRead ("shaders/lamp-vertex-shader.glsl");
    const GLchar* lampFragmentShaderSource;
    lampFragmentShaderSource = fileRead ("shaders/lamp-fragment-shader.glsl");

    GLuint lampVertexShader; 
    lampVertexShader = shaderCreate (lampVertexShaderSource, GL_VERTEX_SHADER);
    GLuint lampFragmentShader;
    lampFragmentShader = shaderCreate (lampFragmentShaderSource, 
            GL_FRAGMENT_SHADER);

    GLuint lampShaders[] = {lampVertexShader, lampFragmentShader};
    GLuint lampShaderProgram = shaderLink (lampShaders);

    /* Cube object */
    glUseProgram (cubeShaderProgram);

    GLint cubeModelLoc = glGetUniformLocation (cubeShaderProgram, 
            "modelMatrix");
    GLint cubeViewLoc = glGetUniformLocation (cubeShaderProgram, 
            "viewMatrix");
    GLint cubeProjLoc = glGetUniformLocation (cubeShaderProgram, 
            "projectionMatrix");
    GLint cubeNormLoc = glGetUniformLocation (cubeShaderProgram,
            "normalMatrix");

    mat4 cubeModel = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    cubeModel = mat4Mult (mat4Rotate ((vec3){1, 0, 0}, 0), cubeModel);
    cubeModel = mat4Mult (mat4Rotate ((vec3){0, 1, 0}, 0), cubeModel);
    cubeModel = mat4Mult (mat4Rotate ((vec3){0, 0, 1}, 0), cubeModel);
    cubeModel = mat4Mult (mat4Translate ((vec3){0, 0, 0}), cubeModel);

    mat4 cn = mat4Transpose (mat4Inv (cubeModel));
    mat3 cubeNorm = (mat3){
        cn.a, cn.b, cn.c,
        cn.e, cn.f, cn.g,
        cn.i, cn.j, cn.k
    };
    
    GLint cubeShininessLoc = glGetUniformLocation (cubeShaderProgram, 
            "material.shininess");

    GLint lampAmbientLoc = glGetUniformLocation (cubeShaderProgram,
            "lamp.ambient");
    GLint lampDiffuseLoc = glGetUniformLocation (cubeShaderProgram,
            "lamp.diffuse");
    GLint lampSpecularLoc = glGetUniformLocation (cubeShaderProgram,
            "lamp.specular");
    GLint lampPositionLoc = glGetUniformLocation (cubeShaderProgram,
            "lamp.position");

    glUniform1f (cubeShininessLoc, 64.0f);

    glUniform3f (lampAmbientLoc, 0.2f, 0.2f, 0.2f);
    glUniform3f (lampDiffuseLoc, 1.0f, 1.0f, 1.0f);
    glUniform3f (lampSpecularLoc, 1.0f, 1.0f, 1.0f);
    glUniform3f (lampPositionLoc, lampPos.x, lampPos.y, lampPos.z);

    GLuint cubeVAO;
    GLuint cubeVBO;

    GLfloat cubeModelArray[16];
    GLfloat cubeViewArray[16];
    GLfloat cubeProjArray[16];
    GLfloat cubeNormArray[9];

    mat4GLArray (cubeModel, cubeModelArray);
    mat3GLArray (cubeNorm, cubeNormArray);

    glGenVertexArrays (1, &cubeVAO);
    glGenBuffers (1, &cubeVBO);

    glBindBuffer (GL_ARRAY_BUFFER, cubeVBO);
    glBufferData (GL_ARRAY_BUFFER,
                  sizeof (vertices),
                  vertices,
                  GL_STATIC_DRAW);

    glBindVertexArray (cubeVAO);
    glBindBuffer (GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
            (GLvoid*)0);
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
            (GLvoid*)(3 * sizeof (GLfloat)));
    glEnableVertexAttribArray (1);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
            (GLvoid*)(6 * sizeof (GLfloat)));
    glEnableVertexAttribArray (2);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindVertexArray (0);

    /* Lamp object */
    glUseProgram (lampShaderProgram);

    GLint lampModelLoc = glGetUniformLocation (lampShaderProgram, 
            "modelMatrix");
    GLint lampViewLoc = glGetUniformLocation (lampShaderProgram, 
            "viewMatrix");
    GLint lampProjLoc = glGetUniformLocation (lampShaderProgram, 
            "projectionMatrix");

    mat4 lampModel = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    lampModel = mat4Mult (mat4Scale ((vec3){0.5, 0.5, 0.5}), lampModel);
    lampModel = mat4Mult (mat4Rotate ((vec3){1, 0, 0}, 0), lampModel);
    lampModel = mat4Mult (mat4Rotate ((vec3){0, 1, 0}, 0), lampModel);
    lampModel = mat4Mult (mat4Rotate ((vec3){0, 0, 1}, 0), lampModel);
    lampModel = mat4Mult (mat4Translate (lampPos), lampModel);

    GLfloat lampModelArray[16];
    GLfloat lampViewArray[16];
    GLfloat lampProjArray[16];

    mat4GLArray (lampModel, lampModelArray);

    GLuint lampVAO;
    glGenVertexArrays (1, &lampVAO);

    glBindVertexArray (lampVAO);
    glBindBuffer (GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
            (GLvoid*)0);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindVertexArray (0);

    /* Perspective projection */
    mat4 projection = mat4Perspective (pi / 2, (float)WIDTH / (float)HEIGHT, 
                                       0.01f, 100.0f);

    /* Uniforms */
    GLint lampPosLoc = glGetUniformLocation (cubeShaderProgram, 
            "lamp.position");
    GLint viewPosLoc = glGetUniformLocation (cubeShaderProgram, 
            "viewPos");
    GLint lightColourLoc = glGetUniformLocation (lampShaderProgram, 
            "lightColour");

    /* Textures */
    glUseProgram (cubeShaderProgram);
    GLint cubeDiffuseLoc = glGetUniformLocation (cubeShaderProgram, 
            "material.diffuse");
    glUniform1i (cubeDiffuseLoc, 0);
    GLint cubeSpecularLoc = glGetUniformLocation (cubeShaderProgram,
            "material.specular");
    glUniform1i (cubeSpecularLoc, 1);

    GLuint diffuseMap = textureCreate ("images/container2.png");
    GLuint specularMap = textureCreate ("images/container2_specular.png");

    /* Render code executed in main loop */
    int renderUpdate (){
        glClearColor (0.1f, 0.1f, 0.1f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 view = mat4LookAt (cameraPosition, 
                vec3Add (cameraPosition, cameraForward), up);
              
        /* Cube */
        glUseProgram (cubeShaderProgram);

        glActiveTexture (GL_TEXTURE0);
        glBindTexture (GL_TEXTURE_2D, diffuseMap);
        glActiveTexture (GL_TEXTURE1);
        glBindTexture (GL_TEXTURE_2D, specularMap);

        glUniform3f (lampPosLoc, lampPos.x,
                                 lampPos.y,
                                 lampPos.z);
        glUniform3f (viewPosLoc, cameraPosition.x,
                                 cameraPosition.y,
                                 cameraPosition.z);

        mat4GLArray (view, cubeViewArray);
        mat4GLArray (projection, cubeProjArray);

        glUniformMatrix4fv (cubeViewLoc, 1, GL_FALSE, cubeViewArray);
        glUniformMatrix4fv (cubeProjLoc, 1, GL_FALSE, cubeProjArray);
        glUniformMatrix4fv (cubeModelLoc, 1, GL_FALSE, cubeModelArray);
        glUniformMatrix4fv (cubeNormLoc, 1, GL_FALSE, cubeNormArray);

        glBindVertexArray (cubeVAO);
        glDrawArrays (GL_TRIANGLES, 0, 36);
        glBindVertexArray (0);

        /* Lamp */
        glUseProgram (lampShaderProgram);
        glUniform3f (lightColourLoc, 1.0f, 1.0f, 1.0f);

        mat4GLArray (view, lampViewArray);
        mat4GLArray (projection, lampProjArray);

        glUniformMatrix4fv (lampViewLoc, 1, GL_FALSE, lampViewArray);
        glUniformMatrix4fv (lampProjLoc, 1, GL_FALSE, lampProjArray);
        glUniformMatrix4fv (lampModelLoc, 1, GL_FALSE, lampModelArray);

        glBindVertexArray (lampVAO);
        glDrawArrays (GL_TRIANGLES, 0, 36);
        glBindVertexArray (0);

        return 0; 
    }

    /* Main loop */
    flowMain (window, &renderUpdate, &gameUpdate);

    /* Cleanly exit */
    flowExit ();
    return 0;
}
