#ifndef OPENGLOPERATIONS_H
#define OPENGLOPERATIONS_H


#include <fstream>
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <sstream>
#include <string>


GLFWwindow* InitializeOpenGL();

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

void ProcessInput(GLFWwindow* window);

#endif // !OPENGLOPERATIONS_H