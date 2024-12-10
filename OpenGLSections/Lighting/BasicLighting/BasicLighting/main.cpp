//Core Libraries
#include <stdio.h>
#include <stdlib.h>

//Custom Libraries
#include "Camera.h"
#include "OpenGLOperations.h"
#include "Shader.h"
#include "stb_image.h"

//--------------------------------------------------------------

glm::vec3 camPos(0.0f, 0.0f, 3.0f);
glm::vec3 camFwd(0.0f, 0.0f, -1.0f);
glm::vec3 camUp(0.0f, 1.0f, 0.0f);
Camera mainCamera(camPos, camFwd, camUp);



//--------------------------------------------------------------


/// <summary>
/// Processes input from user
/// </summary>
/// <param name="window">window to take input from</param>
void ProcessInput(GLFWwindow* window);

/// <summary>
/// wrapper function to call objects cursor function
/// </summary>
/// <param name="window">The window to track mouse movements</param>
/// <param name="xPos">X position of the mouse</param>
/// <param name="yPos">Y position of the mouse</param>
void mainCam_cursor_wrapper(GLFWwindow* window, double xPos, double yPos);

/// <summary>
/// wrapper function to call objects scroll wheel function
/// </summary>
/// <param name="window">The window the callback executes on</param>
/// <param name="xOffset">The FOV offset to apply on the X axis</param>
/// <param name="yOffset">The FOV offset to apply on the Y axis</param>
void mainCam_scroll_wrapper(GLFWwindow* window, double xOffset, double yOffset);



int main()
{
	

	return 0;
}



void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        mainCamera.ProcessInput(GLFW_KEY_W);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        mainCamera.ProcessInput(GLFW_KEY_S);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        mainCamera.ProcessInput(GLFW_KEY_D);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        mainCamera.ProcessInput(GLFW_KEY_A);
    }
}

void mainCam_cursor_wrapper(GLFWwindow* window, double xPos, double yPos)
{
    mainCamera.mouse_callback(window, xPos, yPos);
}

void mainCam_scroll_wrapper(GLFWwindow* window, double xOffset, double yOffset)
{
    mainCamera.scroll_callback(window, xOffset, yOffset);
}