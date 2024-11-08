#include "Camera.h"

void Camera::ProcessInput(GLFWwindow* window)
{

}

void Camera::GenerateProjectionMatrix(float& windowWidth, float& windowHeight, float& near, float& far)
{
	projMatrix = glm::mat4(1.0f);
	projMatrix = glm::perspective(glm::radians(fov), windowWidth / windowHeight, near, far);
}

void Camera::mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos; // moving mouse up moves pitch up
}