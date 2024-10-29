#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// Read in glsl shader data
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexStream(vertexPath);
	std::ifstream fragmentStream(fragmentPath);

	if (!vertexStream.is_open())
	{
		std::cout << "failed to open vertex stream" << std::endl;
		return;
	}

	if (!fragmentStream.is_open())
	{
		std::cout << "failed to open fragment stream" << std::endl;
		return;
	}

	std::stringstream vertexSS;
	vertexSS << vertexStream.rdbuf();
	vertexStream.close();
	vertexCode = vertexSS.str();

	std::stringstream fragmentSS;
	fragmentSS << fragmentStream.rdbuf();
	fragmentStream.close();
	fragmentCode = fragmentSS.str();

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	// Create vertex and fragment shaders
	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program
	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
