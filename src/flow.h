#ifndef FLOW_H
#define FLOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

float timeDelta;
double timeCurrFrame;
double timeLastFrame;

GLFWwindow* flowInit (int width, int height, char* name);
int flowMain (GLFWwindow* window, int (*renderUpdate) (), int (*gameUpdate) ());
int flowExit ();

#endif
