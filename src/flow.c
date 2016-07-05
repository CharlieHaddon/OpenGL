#include "flow.h"

GLFWwindow* flowInit (int width, int height, char* name){
    /* Initialise glfw */
    glfwInit ();
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_RESIZABLE, GL_FALSE);

    /* Create window */
    GLFWwindow* window = glfwCreateWindow (width, height, name, NULL, NULL);
    if (window == NULL){
        fprintf (stderr, "INIT: Failed to create window.\n");
        glfwTerminate ();
        return NULL;
    }
    glfwMakeContextCurrent (window); 

    /* Initialise glew */
    glewExperimental = GL_TRUE;
    GLenum glewInitState = glewInit ();
    if (glewInitState != GLEW_OK){
        fprintf (stderr, "INIT: Failed to initialise glew: %s\n",
                glewGetErrorString (glewInitState));
    }
    
    /* Create viewport */
    int viewWidth, viewHeight;
    glfwGetFramebufferSize (window, &viewWidth, &viewHeight);
    glViewport (0, 0, viewWidth, viewHeight);

    return window;
}

int flowMain (GLFWwindow* window, int (*renderFrame) ()){
    /* Main loop */
    while (!glfwWindowShouldClose (window)){
        glfwPollEvents ();
        (*renderFrame) ();
        glfwSwapBuffers (window);
    }
    return 0;
}

int flowExit (){
    /* Cleanly exit */
    glfwTerminate ();
    return 0;
}
