//Core Libraries
#include <stdio.h>
#include <stdlib.h>

//Custom Libraries
#include "Camera.h"
#include "OpenGLOperations.h"
#include "Shader.h"
#include "stb_image.h"

//--------------------------------------------------------------

// Window size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// delta time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Camera
glm::vec3 camPos(0.0f, 0.0f, 3.0f);
glm::vec3 camFwd(0.0f, 0.0f, -1.0f);
Camera mainCamera(camPos, camFwd);

//--------------------------------------------------------------


/// <summary>
/// Processes input from user
/// </summary>
/// <param name="window">window to take input from</param>
void ProcessInput(GLFWwindow* window);


int main()
{
    // initialize openGL
    GLFWwindow* window = InitializeOpenGL("BasicLighting", WINDOW_WIDTH, WINDOW_HEIGHT);

    // Cursor callback
    auto cursorLambda = [](GLFWwindow* window, double xPos, double yPos) {
        mainCamera.RotateCameraInput(window, xPos, yPos);
        };
    glfwSetCursorPosCallback(window, cursorLambda);

    // scroll callback
    auto scrollLambda = [](GLFWwindow* window, double xOffset, double yOffset) {
        mainCamera.ZoomCameraInput(window, xOffset, yOffset);
        };
    glfwSetScrollCallback(window, scrollLambda);

    // lock cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Vertices to create a cube
    float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        // handle delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // user input & delta speed adjustments
        float origCamSpeed = mainCamera.GetCameraSpeed();
        float deltaCamSpeed = origCamSpeed * deltaTime;
        mainCamera.SetCameraSpeed(deltaCamSpeed);
        ProcessInput(window);
        mainCamera.SetCameraSpeed(origCamSpeed);

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // cube
        glm::vec3 camPos = mainCamera.GetCameraPosition();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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