#include "OpenGLOperations.h"
#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>

// TODO: Do shader exercises

int main()
{
	GLFWwindow* window = InitializeOpenGL();

	Shader shader("Shaders\\VertexShader1.glsl", "Shaders\\FragmentShader1.glsl");
	Shader offsetShader("Shaders\\VertexOffsetShader.glsl", "Shaders\\FragmentOffsetShader.glsl");

	float Triangle1[] = {
		// Vertices         // Colors
		-1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom Left
		0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Top
	};

	float Triangle2[] = {
		1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
	};

	unsigned int VAO[2];
	glGenVertexArrays(2, VAO);

	unsigned int VBO[2];
	glGenBuffers(2, VBO);

	// initialize VAO 1
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle1), Triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// initialize VAO2
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2), Triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	

	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render
		shader.Use();


		//Bind VAO 1
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		
		offsetShader.Use();

		//Bind VAO2
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//Swap color buffer and shows output to screen
		glfwSwapBuffers(window);

		//check if any events triggered
		glfwPollEvents();
	}


	// Clean-up
	glDeleteProgram(shader.ID);
	glfwTerminate();

	return 0;
}