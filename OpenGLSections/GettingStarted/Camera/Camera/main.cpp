// Core Libraries
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <functional>

// Personal/External Libraries
#include "Camera.h"
#include "OpenGLOperations.h"
#include "Shader.h"
#include "stb_image.h"

// DeltaTime
float deltaTime = 0.0f; // Time between current and last frame
float lastFrame = 0.0f; // Time of last frame

// Create global camera for the scene
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // Cameras starting position
glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f); // Cameras direction pointing forward
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Cameras Up position
Camera mainCamera(cameraPos, cameraDir, cameraUp);

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
	GLFWwindow* window = InitializeOpenGL("Camera");
	Shader woodenShader("Shaders//WoodenVertexShader.glsl", "Shaders//WoodenFragmentShader.glsl");

	// hides mouse and keeps it at center of the screen
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mainCam_cursor_wrapper);
	glfwSetScrollCallback(window, mainCam_scroll_wrapper);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	unsigned int VBO, VAO,TBO1, TBO2;

	// Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Buffer Objects & loading textures
	glGenTextures(1, &TBO1);
	glBindTexture(GL_TEXTURE_2D, TBO1);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, woodNRChannel;
	unsigned char* woodTextureData = stbi_load("Textures//woodencontainer.jpg", &width, &height, &woodNRChannel, 0);
	if (woodTextureData != nullptr)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, woodTextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}
	stbi_image_free(woodTextureData);

	glGenTextures(1, &TBO2);
	glBindTexture(GL_TEXTURE_2D, TBO2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width2, height2, NrChannel2;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* faceTextureData = stbi_load("Textures//awesomeface.png", &width2, &height2, &NrChannel2, 0);
	if (faceTextureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceTextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}
	stbi_image_free(faceTextureData);

	// must use shader to set uniform values
	woodenShader.Use();
	woodenShader.setInt("firstTexture", 0);
	woodenShader.setInt("secondTexture", 1);
	
	// enable depth testing so fragments dont overlap incorrectly
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		float origCamSpeed = mainCamera.GetCameraSpeed();
		float deltaCamSpeed = mainCamera.GetCameraSpeed() * deltaTime;
		//mainCamera.SetCameraSpeed(deltaCamSpeed);
		ProcessInput(window);
		//mainCamera.SetCameraSpeed(origCamSpeed);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TBO1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TBO2);
		woodenShader.Use();

		// Projection Matrix (makes objects further away smaller to give more realistic look)
		mainCamera.GenerateProjectionMatrix(400.0f, 300.0f, 0.1f, 100.0f);
		int projLoc = glGetUniformLocation(woodenShader.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mainCamera.GetProjMatrix()));

		glBindVertexArray(VAO);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
			float angle = 20.0f * i;

			if (i % 3 == 0)
			{
				modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			}
			else
			{
				modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			}
			

			int modelLoc = glGetUniformLocation(woodenShader.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			// View Matrix (moves world around for camera view)
			glm::mat4 viewMatrix;
			viewMatrix = glm::lookAt(cameraPos, (cameraPos + cameraDir), cameraUp);

			int viewLoc = glGetUniformLocation(woodenShader.ID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//Swap color buffer and shows output to screen
		glfwSwapBuffers(window);

		//check if any events triggered
		glfwPollEvents();
	}


	// Clean-up
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &TBO1);
	glDeleteTextures(1, &TBO2);
	glDeleteShader(woodenShader.ID);
	glfwTerminate();

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