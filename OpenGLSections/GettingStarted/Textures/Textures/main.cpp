// Core Libraries
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

// Personal/External Libraries
#include "OpenGLOperations.h"
#include "Shader.h"
#include "stb_image.h"

// TODO: continue on "Texture Units" section of Textures lesson in OpenGL

int main()
{
	GLFWwindow* window = InitializeOpenGL("Textures");
	Shader woodenShader("WoodenTileVertexShader.glsl", "WoodenTileFragmentShader.glsl");

	float TileVertices[] = {
		// positions        // colors           // texture coords
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom left
		-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f   // top left
	};

	unsigned int ShapeIndices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	// initialize VAO & VBO
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TileVertices), TileVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ShapeIndices), ShapeIndices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Initialize textures
	unsigned int woodenTexture;
	glGenTextures(1, &woodenTexture);
	glBindTexture(GL_TEXTURE_2D, woodenTexture);

	// set texture wrapping/filtering options on currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load texture image
	int woodenWidth, woodenHeight, woodenNrChannels;
	unsigned char* woodenTextureData = stbi_load("TextureResources//woodencontainer.jpg", &woodenWidth, &woodenHeight, &woodenNrChannels, 0);
	if (woodenTextureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, woodenWidth, woodenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, woodenTextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(woodenTextureData);

	unsigned int happyFaceTexture;
	glGenTextures(1, &happyFaceTexture);
	glBindTexture(GL_TEXTURE_2D, happyFaceTexture);

	// set texture wrapping/filtering options on currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int happyFaceWidth, happyFaceHeight, happyFaceNrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* happyFaceTextureData = stbi_load("TextureResources//awesomeface.png", &happyFaceWidth, &happyFaceHeight, &happyFaceNrChannels, 0);
	if (happyFaceTextureData)
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, happyFaceWidth, happyFaceHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, happyFaceTextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(happyFaceTextureData);

	woodenShader.Use();
	woodenShader.setInt("woodenTexture", 0);
	woodenShader.setInt("happyFaceTexture", 1);

	float visibilityValue = 0.2;
	woodenShader.setFloat("visibility", visibilityValue);
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			if (visibilityValue <= 1.0)
			{
				visibilityValue += 0.01;
				woodenShader.setFloat("visibility", visibilityValue);
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			if (visibilityValue >= 0)
			{
				visibilityValue -= 0.01;
				woodenShader.setFloat("visibility", visibilityValue);
			}
		}

		// bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodenTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, happyFaceTexture);

		//render shader
		woodenShader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		//Swap color buffer and shows output to screen
		glfwSwapBuffers(window);

		//check if any events triggered
		glfwPollEvents();
	}


	// Clean-up
	glDeleteProgram(woodenShader.ID);
	glfwTerminate();

	return 0;
}