// Core Libraries
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

// GLM Libraries
#include "../../ExternalLibraries/glm/glm.hpp"
#include "../../ExternalLibraries/glm/gtc/matrix_transform.hpp"
#include "../../ExternalLibraries/glm/gtc/type_ptr.hpp"

// Personal/External Libraries
#include "OpenGLOperations.h"
#include "Shader.h"
#include "stb_image.h"

int main()
{
	GLFWwindow* window = InitializeOpenGL("Translations");

	Shader woodenShader1("Shaders//WoodenVertexShader.glsl", "Shaders//WoodenFragmentShader.glsl");
	Shader woodenShader2("Shaders//WoodenVertexShader.glsl", "Shaders//WoodenFragmentShader.glsl");
	
	float vertices[]{
		0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
		0.5f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f,// top right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,// bottom left
		-0.5f, 0.5f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f// top left
	};

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 1
	};

	unsigned int VBO, VAO, EBO, TBO1, TBO2;

	// Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element Buffer Object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

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
	woodenShader1.Use();
	woodenShader1.setInt("firstTexture", 0);
	woodenShader1.setInt("secondTexture", 1);

	woodenShader2.Use();
	woodenShader2.setInt("firstTexture", 0);
	woodenShader2.setInt("secondTexture", 1);

	// get mat4 location in vertex shader
	unsigned int transMatrix1 = glGetUniformLocation(woodenShader1.ID, "transform");
	unsigned int transMatrix2 = glGetUniformLocation(woodenShader2.ID, "transform");
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// First object render
		glm::mat4 woodTransMatrix1 = glm::mat4(1.0f);
		woodTransMatrix1 = glm::translate(woodTransMatrix1, glm::vec3(0.5f, -0.5f, 0.0f));
		woodTransMatrix1 = glm::rotate(woodTransMatrix1, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TBO1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TBO2);
		woodenShader1.Use();
		glUniformMatrix4fv(transMatrix1, 1, GL_FALSE, glm::value_ptr(woodTransMatrix1));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

		// Second object render
		glm::mat4 woodTransMatrix2 = glm::mat4(1.0f);
		woodTransMatrix2 = glm::translate(woodTransMatrix2, glm::vec3(-0.5f, 0.5f, 0.0f));
		woodTransMatrix2 = glm::scale(woodTransMatrix2, glm::vec3(glm::sin((double)glfwGetTime()),
			glm::sin((double)glfwGetTime()),
			glm::sin((double)glfwGetTime())));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TBO1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TBO2);
		woodenShader2.Use();
		glUniformMatrix4fv(transMatrix2, 1, GL_FALSE, glm::value_ptr(woodTransMatrix2));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
		
		//Swap color buffer and shows output to screen
		glfwSwapBuffers(window);

		//check if any events triggered
		glfwPollEvents();
	}


	// Clean-up
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &TBO1);
	glDeleteTextures(1, &TBO2);
	glDeleteShader(woodenShader1.ID);
	glDeleteShader(woodenShader2.ID);
	glfwTerminate();

	return 0;
}