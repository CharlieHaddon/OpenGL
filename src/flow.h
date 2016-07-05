#ifndef FLOW_H
#define FLOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

GLFWwindow* flowInit (int width, int height, char* name);
int flowMain (GLFWwindow* window, int (*renderFrame) ());
int flowExit ();

#endif
