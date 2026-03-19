//
// Created by canyo on 3/17/2026.
//

#ifndef DAGRANDRENDERER_SHADER_H
#define DAGRANDRENDERER_SHADER_H

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>



class Shader
{
private:
    unsigned int shaderProgram = -1;

public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        std::ifstream vertexFile(vertexShaderPath);
    if (vertexFile.fail())
    {
        std::cout << "Failed to find vertex shader path: " << vertexShaderPath << ". Can't make the shader object" << std::endl;
        vertexFile.close();
        return;
    }

    std::ifstream fragmentFile(fragmentShaderPath);
    if (fragmentFile.fail())
    {
        std::cout << "Failed to find fragment shader path: " << fragmentShaderPath << ". Can't make the shader object" << std::endl;
        fragmentFile.close();
        return;
    }

    std::stringstream vertexBuf;
    vertexBuf >> vertexFile.rdbuf();
    const char* vertexSource = vertexBuf.str().c_str();
    vertexFile.close();

    std::stringstream fragmentBuf;
    fragmentBuf >> fragmentFile.rdbuf();
    const char* fragmentSource = fragmentBuf.str().c_str();
    fragmentFile.close();

    unsigned int vertex;
    glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, nullptr);
    glCompileShader(vertex);
    int success;
    char infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "Error, vertex shader failed to compile\n" << infoLog << std::endl;
        return;
    }

    unsigned int fragment;
    glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "Error, fragment shader failed to compile\n" << infoLog << std::endl;
        return;
    }


    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Error, shader program failed to compile\n" << infoLog << std::endl;
        return;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    }

};

#endif //DAGRANDRENDERER_SHADER_H