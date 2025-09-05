#ifndef OPENGLOPERATIONS_H
#define OPENGLOPERATIONS_H


#include <fstream>
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <sstream>
#include <string>

// GLM Libraries
#include "glm.hpp"
#include "../../ExternalLibraries/glm/gtc/matrix_transform.hpp"
#include "../../ExternalLibraries/glm/gtc/type_ptr.hpp"


/// <summary>
/// A function library consisting of regular operations needed in OpenGL
/// </summary>
class OpenGLHelpers
{

public:

	/// <summary>
	/// Initializes external libraries and a window to be used for rendering
	/// </summary>
	/// <param name="windowName">The name the window will be called</param>
	/// <returns>Pointer to the window upon successful initialization of all libraries</returns>
	static GLFWwindow* InitializeOpenGL(const std::string& windowName, const int& width, const int& height);

	/// <summary>
	/// Generates a preset 2D texture buffer with a valid image path passed in
	/// </summary>
	/// <param name="texturePath"> Path to the texture/image in the project
	/// <returns>texture buffer if successful</returns>
	static unsigned int Generate2DTextureBuffer(const char* texturePath);

private:

	/// <summary>
	/// Callback function that gets called each time the window is resized
	/// </summary>
	/// <param name="window">The window that will be resized</param>
	/// <param name="width">Width of the window</param>
	/// <param name="height">Height of the window</param>
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

#endif // !OPENGLOPERATIONS_H