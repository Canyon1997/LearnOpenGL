#pragma once

// OpenGL
#include <GLFW/glfw3.h>
#include <glad/glad.h>

/// @brief
///    Initializes all the core glfw and glad processes
/// @return
///    A pointer to the window to use for rendering
GLFWwindow* initializeOpenGL();

/// @brief
///    Moment user resizes the window, viewport should b e adjusted as well
///    Callback function that gets called each time window is resized
/// @param window
///    Window to be resized
/// @param width
///    Width the window should be set to
/// @param height
///    Height the window should be set to
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/// @brief
///    Takes window as input together with a key
/// @param window
///    The window to take input from
void processInput(GLFWwindow* window);

/// @brief
///    Creates and binds a vertex shader
/// @return
///    unsigned int ID of the vertex shader created
unsigned int createVertexShader(const char* vertexShaderSource);

/// @brief
///    Creates and binds a fragment shader
/// @return
///    unsigned int ID of the fragment shader created
unsigned int createFragmentShader(const char* fragmentShaderSource);

/// @brief
///    binds vertex and fragment shader to create shader program
/// @return
///    unsigned int ID of the shader program created
unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);