#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <string>
#include <windows.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

// init functions
bool initGlfw();
bool initGlad();

// window functions
GLFWwindow* createGlfwWindow(int width, int height, const std::string& windowName);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// input
void ProcessInput(GLFWwindow* currentWindow);


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

    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    unsigned int vertexShader;

    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
    unsigned int fragmentShader;

    const char *fragmentShaderYellowSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";
    unsigned int fragmentYellowShader;

    float objVertexData1[] = {
        -1.0f, 0.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    float objVertexData2[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    unsigned int objectIndices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    unsigned int VBO1;
    unsigned int VAO1;

    glGenBuffers(1, &VBO1);
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objVertexData1), objVertexData1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int VBO2;
    unsigned int VAO2;
    glGenBuffers(1, &VBO2);
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objVertexData2), objVertexData2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Error, vertex shader failed to compile\n" << infoLog << std::endl;
        return -1;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Error, fragment shader failed to compile\n" << infoLog << std::endl;
        return -1;
    }

    fragmentYellowShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentYellowShader, 1, &fragmentShaderYellowSource, nullptr);
    glCompileShader(fragmentYellowShader);
    glGetShaderiv(fragmentYellowShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentYellowShader, 512, nullptr, infoLog);
        std::cout << "Error, fragment shader failed to compile\n" << infoLog << std::endl;
        return -1;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Error, shader program failed to compile\n" << infoLog << std::endl;
        return -1;
    }

    unsigned int shaderYellowProgram;
    shaderYellowProgram = glCreateProgram();
    glAttachShader(shaderYellowProgram, vertexShader);
    glAttachShader(shaderYellowProgram, fragmentYellowShader);
    glLinkProgram(shaderYellowProgram);
    glGetProgramiv(shaderYellowProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderYellowProgram, 512, nullptr, infoLog);
        std::cout << "Error, shader program failed to compile\n" << infoLog << std::endl;
        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentYellowShader);

    while (!glfwWindowShouldClose(mainWindow))
    {
        // input
        ProcessInput(mainWindow);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO1);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderYellowProgram);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check/call events, swap buffers, etc.
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void ProcessInput(GLFWwindow* currentWindow)
{
    if (glfwGetKey(currentWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
    }
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
