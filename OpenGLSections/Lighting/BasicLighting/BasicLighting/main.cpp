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
glm::vec3 camUp(0.0f, 1.0f, 0.0f);
Camera mainCamera(camPos, camFwd, camUp);


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
    GLFWwindow* window = InitializeOpenGL("BasicLighting", WINDOW_WIDTH, WINDOW_HEIGHT);
    Shader cubeShader = Shader("Shaders//CubeVertex.glsl", "Shaders//CubeFragment.glsl");
    Shader lightSourceShader = Shader("Shaders//LightSourceVertex.glsl", "Shaders//LightSourceFragment.glsl");

    glfwSetCursorPosCallback(window, mainCam_cursor_wrapper);
    glfwSetScrollCallback(window, mainCam_scroll_wrapper);
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

    unsigned int cubeVBO;
    unsigned int cubeVAO;
    glGenBuffers(1, &cubeVBO);
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


  
    unsigned int lightSourceVAO;
    glGenVertexArrays(1, &lightSourceVAO);
    glBindVertexArray(lightSourceVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

        //Rotate light source horizontally
        lightPos.x = glm::cos(glfwGetTime()) * 2.0f;
        lightPos.z = glm::sin(glfwGetTime()) * 2.0f;

        // cube
        glm::vec3 camPos = mainCamera.GetCameraPosition();
        cubeShader.Use();
        cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        cubeShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
        cubeShader.setVec3("viewPos", camPos.x, camPos.y, camPos.z);

        mainCamera.GenerateProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT, 0.1f, 100.0f);
        int cubeProj = glGetUniformLocation(cubeShader.ID, "proj");
        glUniformMatrix4fv(cubeProj, 1, GL_FALSE, glm::value_ptr(mainCamera.GetProjMatrix()));

        mainCamera.GenerateViewMatrix();
        int cubeView = glGetUniformLocation(cubeShader.ID, "view");
        glUniformMatrix4fv(cubeView, 1, GL_FALSE, glm::value_ptr(mainCamera.GetViewMatrix()));

        glm::mat4 model = glm::mat4(1.0f);
        int cubeModel = glGetUniformLocation(cubeShader.ID, "model");
        glUniformMatrix4fv(cubeModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        //light source
        lightSourceShader.Use();

        int lightProj = glGetUniformLocation(lightSourceShader.ID, "proj");
        glUniformMatrix4fv(lightProj, 1, GL_FALSE, glm::value_ptr(mainCamera.GetProjMatrix()));

        int lightView = glGetUniformLocation(lightSourceShader.ID, "view");
        glUniformMatrix4fv(lightView, 1, GL_FALSE, glm::value_ptr(mainCamera.GetViewMatrix()));

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        int lightModel = glGetUniformLocation(lightSourceShader.ID, "model");
        glUniformMatrix4fv(lightModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(lightSourceVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightSourceVAO);
    glDeleteBuffers(1, &cubeVBO);

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
    mainCamera.RotateCameraInput(window, xPos, yPos);
}

void mainCam_scroll_wrapper(GLFWwindow* window, double xOffset, double yOffset)
{
    mainCamera.ZoomCameraInput(window, xOffset, yOffset);
}