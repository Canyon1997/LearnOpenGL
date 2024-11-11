#include "Camera.h"

void Camera::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camPos += cameraSpeed * camForwardDir;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camPos -= cameraSpeed * camForwardDir;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camPos += glm::normalize(glm::cross(camForwardDir, camUpDir)) * cameraSpeed;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camPos -= glm::normalize(glm::cross(camForwardDir, camUpDir)) * cameraSpeed;
	}
}

void Camera::GenerateProjectionMatrix(float windowWidth, float windowHeight, float near, float far)
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

	lastX = xPos;
	lastY = yPos;

	xOffset *= mouseSens;
	yOffset *= mouseSens;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camForwardDir = glm::normalize(direction);
}

void Camera::scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	fov -= (float)yOffset;

	if (fov > 90.0f)
	{
		fov = 90.0f;
	}
	
	if (fov < 1.0f)
	{
		fov = 1.0f;
	}
}