
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <functional>

#include "Camera.h"
#include "OpenGLOperations.h"
#include "Shader.h"
#include "stb_image.h"

// delta time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// window size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Camera
glm::vec3 CameraPos(0.0f, 0.0f, 3.0f);
glm::vec3 CameraForward(0.0f, 0.0f, -1.0f);
glm::vec3 CameraUp(0.0f, 1.0f, 0.0f);
Camera mainCamera(CameraPos, CameraForward, CameraUp);

// light source
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//--------------------------------------------------------------


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
	GLFWwindow* window = InitializeOpenGL("Colors", WINDOW_WIDTH, WINDOW_HEIGHT);

    Shader cubeShader("Shaders//WoodenVertexShader.glsl", "Shaders//WoodenFragmentShader.glsl");
    Shader lightShader("Shaders//LightVertex.glsl", "Shaders//LightFragment.glsl");

    glfwSetCursorPosCallback(window, mainCam_cursor_wrapper);
    glfwSetScrollCallback(window, mainCam_scroll_wrapper);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // Data for object to show in scene with light reflected on it
    float CubeVertices[] = {
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

    unsigned int cubeVBO;
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_VERTEX_ARRAY, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float), CubeVertices, GL_STATIC_DRAW);

    unsigned int cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int woodTBO;
    glGenTextures(1, &woodTBO);
    glBindTexture(GL_TEXTURE_2D, woodTBO);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load wood texture data
    int woodWidth, woodHeight, woodChannel;
    unsigned char* woodTextureData = stbi_load("Textures//woodencontainer.jpg", &woodWidth, &woodHeight, &woodChannel, 0);

    if (woodTextureData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, woodWidth, woodHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, woodTextureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load wood texture data" << std::endl;
        return -1;
    }
    stbi_image_free(woodTextureData);

    // Load smile face texture data
    unsigned int smileTBO;
    glGenTextures(1, &smileTBO);
    glBindTexture(GL_TEXTURE_2D, smileTBO);

    stbi_set_flip_vertically_on_load(true);
    int smileWidth, smileHeight, smileChannel;
    unsigned char* smileTextureData = stbi_load("Textures//awesomeface.png", &smileWidth, &smileHeight, &smileChannel, 0);

    if (smileTextureData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, smileWidth, smileHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, smileTextureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load awesomeface texture data" << std::endl;
        return -1;
    }
    stbi_image_free(smileTextureData);

    cubeShader.Use();
    cubeShader.setInt("firstTexture", 0);
    cubeShader.setInt("secondTexture", 1);



    // Light object to have other objects reflect off of
    float LightVertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
    };

    unsigned int lightVBO;
    glGenBuffers(1, &lightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LightVertices), LightVertices, GL_STATIC_DRAW);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    lightShader.Use();
    lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
        // update delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        // user input / delta speed adjustments
        float origCamSpeed = mainCamera.GetCameraSpeed();
        float deltaCamSpeed = origCamSpeed * deltaTime;
        mainCamera.SetCameraSpeed(deltaCamSpeed);
        ProcessInput(window);
        mainCamera.SetCameraSpeed(origCamSpeed);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	}


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
