#include "input.h"

void keyCallback (GLFWwindow* window, int key, int scancode,
        int action, int mode){
    if (action == GLFW_PRESS)
        keyState[key] = true;
    if (action == GLFW_RELEASE)
        keyState[key] = false;
}

void mouseCallback (GLFWwindow* window, double xPos, double yPos){
    mousex = xPos;
    mousey = yPos;
}
