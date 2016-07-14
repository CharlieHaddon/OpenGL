#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <GLFW/glfw3.h>

bool keyState[1024];

double mousex;
double mousey;
double lastMousex;
double lastMousey;
double mousexOffset;
double mouseyOffset;

void keyCallback (GLFWwindow* window, int key, int scancode, 
        int action, int mode);
void mouseCallback (GLFWwindow* window, double xPos, double yPos);

#endif
