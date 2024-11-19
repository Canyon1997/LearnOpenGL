#ifndef CAMERA_H
#define CAMERA_H

#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "../../ExternalLibraries/glm/gtc/matrix_transform.hpp"

/// <summary>
/// This is a camera class that is used to move/look/zoom within a window
/// </summary>
class Camera
{
private:

	// camera positions
	glm::vec3 camPos;
	glm::vec3 camForwardDir;
	glm::vec3 camUpDir;

	// ProjectionMatrix
	glm::mat4 projMatrix;

	// ViewMatrix
	glm::mat4 viewMatrix;

	// cursor variables
	float lastX = 400;
	float lastY = 300;
	float mouseSens = 0.2f;

	// camera rotation variables
	float pitch = 0.0f;
	float yaw = -90.0f;

	// Speed to move camera around
	float cameraSpeed = 2.0f;

	// camera FOV
	float fov = 45.0f;

	// sets mouse in tact first frame
	bool firstMouse = true;


public:

	/// <summary>
	/// Takes in a camera starting position, its forward direction vector, and its up vector to create an instance of a camera to use in a scene
	/// </summary>
	Camera(const glm::vec3& cameraPos, const glm::vec3& cameraForward, const glm::vec3& cameraUp)
	{
		camPos = cameraPos;
		camForwardDir = cameraForward;
		camUpDir = cameraUp;
	}

	/// <summary>
    /// Callback function to get x & y values from mouse movements each frame
    /// </summary>
    /// <param name="window">The window to track mouse movements</param>
    /// <param name="xPos">X position of the mouse</param>
    /// <param name="yPos">Y position of the mouse</param>
	void mouse_callback(GLFWwindow* window, float xPos, float yPos);

	/// <summary>
	/// Zooms the camera in/out with the scroll wheel
	/// </summary>
	/// <param name="window">The window the callback executes on</param>
	/// <param name="xOffset">The FOV offset to apply on the X axis</param>
	/// <param name="yOffset">The FOV offset to apply on the Y axis</param>
	void scroll_callback(GLFWwindow* window, float xOffset, float yOffset);

	/// <summary>
	/// Takes in input from user keyboard to do things
	/// </summary>
	/// <param name="key">The key that was pressed</param>
	void ProcessInput(int key);

	/// <summary>
	/// Generates projection matrix to pass into shaders
	/// </summary>
	/// <param name="windowWidth">The width of the window this projection matrix is used on</param>
	/// <param name="windowHeight">The height of the window this projection matrix is used on</param>
	/// <param name="near">The closest distance from the camera to start processing things within the projection matrix</param>
	/// <param name="far">The max distance to project things within the projection matrix until things are cut out/ not processed</param>
	void GenerateProjectionMatrix(float windowWidth, float windowHeight, float near, float far);

	/// <summary>
	/// Generates view matrix to pass into shaders
	/// </summary>
	void GenerateViewMatrix();

	/// <summary>
	/// Sets the x axis position of the mouse to start at for calculating movement, etc. in scene.
	/// generally this will be the middle of the window (window width / 2)
	/// </summary>
	/// <param name="xPos">The X-axis position the mouse will start at</param>
	void SetMouseXPosition(const float& xPos)
	{
		lastX = xPos;
	}

	/// <summary>
	/// Sets the y axis position of the mouse to start at for calculating movement, etc. in scene.
	/// generally this will be the middle of the window (window height / 2)
	/// </summary>
	/// <param name="yPos">The y-axis position the mouse will start at</param>
	void SetMouseYPosition(const float& yPos)
	{
		lastY = yPos;
	}

	/// <summary>
	/// Sets the sensitivity of how fast the camera will rotate to look around the scene
	/// </summary>
	/// /// <param name="sens">the value that determines how fast/slow the camera will rotate/look around the scene</param>
	void SetMouseSensitivity(const float& sens)
	{
		mouseSens = sens;
	}

	/// <summary>
	/// Sets the speed of the camera to move around
	/// </summary>
	/// <param name="speed">The value that determines how fast the camera moves around the scene</param>
	void SetCameraSpeed(const float& speed)
	{
		cameraSpeed = speed;
	}

	
	/// <summary>
	/// Gets the projection matrix of the camera to use for things like shaders, etc.
	/// </summary>
	glm::mat4 GetProjMatrix() const
	{
		return projMatrix;
	}

	/// <summary>
	/// Gets the view matrix of the camera to use for things like shaders, etc.
	/// </summary>
	glm::mat4 GetViewMatrix() const
	{
		return viewMatrix;
	}


	/// <summary>
	/// Gets the current speed for the specific camera
	/// </summary>
	float GetCameraSpeed() const
	{
		return cameraSpeed;
	}

};



#endif // !CAMERA_H