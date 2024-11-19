#include "Camera.h"

void Camera::ProcessInput(int key)
{

	switch (key)
	{
	    case GLFW_KEY_W:
			camPos += cameraSpeed * camForwardDir;
			break;

		case GLFW_KEY_S:
			camPos -= cameraSpeed * camForwardDir;
			break;

		case GLFW_KEY_D:
			camPos += glm::normalize(glm::cross(camForwardDir, camUpDir)) * cameraSpeed;
			break;

		case GLFW_KEY_A:
			camPos -= glm::normalize(glm::cross(camForwardDir, camUpDir)) * cameraSpeed;
			break;
	}
	camPos.y = 0.0f; // FPS style, keeps camera from "flying" off xz plane
}

void Camera::GenerateProjectionMatrix(float windowWidth, float windowHeight, float near, float far)
{
	projMatrix = glm::mat4(1.0f);
	projMatrix = glm::perspective(glm::radians(fov), windowWidth / windowHeight, near, far);
}

void Camera::GenerateViewMatrix()
{
	viewMatrix = glm::lookAt(camPos, camPos + camForwardDir, camUpDir);
}

void Camera::mouse_callback(GLFWwindow* window, float xPos, float yPos)
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

void Camera::scroll_callback(GLFWwindow* window, float xOffset, float yOffset)
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