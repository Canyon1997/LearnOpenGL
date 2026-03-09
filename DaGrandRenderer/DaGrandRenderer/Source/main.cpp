#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <string>
#include <windows.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;


bool initGlfw();
bool initGlad();
GLFWwindow* createGlfwWindow(int width, int height, const std::string& windowName);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc, char* argv[])
{
    // init system
    initGlfw();
    GLFWwindow* mainWindow = createGlfwWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DaGrandRenderer");
    glfwMakeContextCurrent(mainWindow);
    if (!initGlad())
    {
        return -1;
    }

    // set current viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(mainWindow, [](GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    });


    while (!glfwWindowShouldClose(mainWindow))
    {
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

bool initGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

bool initGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

GLFWwindow* createGlfwWindow(int width, int height, const std::string& windowName)
{
    GLFWwindow* window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
