#ifndef CAMERA_H
#define CAMERA_H

#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "../../ExternalLibraries/glm/gtc/matrix_transform.hpp"

class Camera
{
private:

	// camera positions
	glm::vec3 camPos;
	glm::vec3 camForwardDir;
	glm::vec3 camUpDir;

	// ProjectionMatrix
	glm::mat4 projMatrix;

	// cursor variables
	float lastX = 400;
	float lastY = 300;
	float mouseSens = 1.0f;

	// camera rotation variables
	float pitch = 0.0f;
	float yaw = -90.0f;

	// camera FOV
	float fov = 45.0f;

	// sets mouse in tact first frame
	bool firstMouse = true;

protected:

	/// <summary>
	/// Callback function to get x & y values from mouse movements each frame
	/// </summary>
	/// <param name="window">The window to track mouse movements</param>
	/// <param name="xPos">X position of the mouse</param>
	/// <param name="yPos">Y position of the mouse</param>
	void mouse_callback(GLFWwindow* window, double xPos, double yPos);

	/// <summary>
	/// Zooms the camera in/out with the scroll wheel
	/// </summary>
	/// <param name="window">The window the callback executes on</param>
	/// <param name="xOffset">The FOV offset to apply on the X axis</param>
	/// <param name="yOffset">The FOV offset to apply on the Y axis</param>
	void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);


public:

	Camera(const glm::vec3& cameraPos, const glm::vec3& cameraForward, const glm::vec3& cameraUp) :
		camPos(cameraPos), camForwardDir(cameraForward), camUpDir(cameraUp) {};

	void ProcessInput(GLFWwindow* window);

	void GenerateProjectionMatrix(float& windowWidth, float& windowHeight, float& near, float& far);

	void SetMouseXPosition(const float& xPos)
	{
		lastX = xPos;
	}

	void SetMouseYPosition(const float& yPos)
	{
		lastY = yPos;
	}

	void SetMouseSensitivity(const float& sens)
	{
		mouseSens = sens;
	}

	glm::mat4 GetProjMatrix() const
	{
		return projMatrix;
	}

};



#endif // !CAMERA_H