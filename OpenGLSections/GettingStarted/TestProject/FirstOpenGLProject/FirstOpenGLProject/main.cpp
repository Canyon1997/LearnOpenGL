/*Libraries*/

//C++
#include <stdio.h>
#include <iostream>

//OpenGL
#include "main.h"


int main(void)
{
	// vertex shader source code
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* orangeFragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	const char* yellowFragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\0";

	GLFWwindow* window = initializeOpenGL();


    // specify vertices for a triangle 
	// Note: these vertices need to be in Normalized Device Coordinates (NDC)
	// x,y,z values between -1.0 and 1.0
	// Any coordinate that falls outside this range will be discarded/clipped
	// and wont be visible on your screen
	float vertices1[] = {
		-1.0f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f
	};

	float vertices2[] = {
		1.0f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f
	};


	unsigned int uniqueIndeces[] = { // starts from 0
		0, 1, 3,
		1, 2, 3
	};



	// Create vertex shader object
	unsigned int vertexShader = createVertexShader(vertexShaderSource);

	// Create fragment shader object
	unsigned int orangeFragmentShader = createFragmentShader(orangeFragmentShaderSource);
	unsigned int yellowFragmentShader = createFragmentShader(yellowFragmentShaderSource);

	// Create shader program
	unsigned int orangeShaderProgram = createShaderProgram(vertexShader, orangeFragmentShader);
	unsigned int yellowShaderProgram = createShaderProgram(vertexShader, yellowFragmentShader);

	// Create a vertex buffer
	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);

	// Create a vertex array object
	unsigned int VAOs[2];
	glGenVertexArrays(2, VAOs);

	// Create element buffer object
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);

	// Bind vertex array object
	glBindVertexArray(VAOs[0]);

	// Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	// Bind element buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Copies previously defined vertex data into buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	// Copies unique indices data into buffer's memory
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uniqueIndeces), uniqueIndeces, GL_STATIC_DRAW);

	// interprets vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Set Size of Rendering Window (in pixels)
	glViewport(0, 0, 800, 600);

	// Create the render loop
	while (!glfwWindowShouldClose(window))
	{
		// Checks for input from the specified window
		processInput(window);

		// Rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// use shader program when we want to render something
		glUseProgram(orangeShaderProgram);

		// bind VAO again with preferred settings before drawing
		glBindVertexArray(VAOs[0]);

		// Draw triangle from index buffer
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(yellowShaderProgram);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swaps color buffer and shows as output to screen
		glfwSwapBuffers(window);

		// Checks if any events are triggered
		glfwPollEvents();
	}

    // delete shader program
	glDeleteProgram(orangeShaderProgram);

	// Clean GLFW resources allocated
	glfwTerminate();
	return 0;
}

GLFWwindow* initializeOpenGL()
{
	// Initialize GLFW and set to version 3.3
	// Tell GLFW to use Core-Profile to get access to smaller subset
	// of OpenGL features without backwards-compatible features we dont need. 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "FirstOpenGLWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	// Registered to be called on every window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

unsigned int createVertexShader(const char* vertexShaderSource)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// attach shader source code to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check if shader compilation was successfull
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return vertexShader;
}

unsigned int createFragmentShader(const char* fragmentShaderSource)
{
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

	}

	return fragmentShader;
}

unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// Attach shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for shader program success
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// delete shader objects, no longer need them after linking to program object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
