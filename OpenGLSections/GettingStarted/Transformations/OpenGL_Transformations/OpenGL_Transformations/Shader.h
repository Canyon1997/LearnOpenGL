#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
public:

	// the program ID
	unsigned int ID;

	// Constructor that takes in the vertex and fragment shader paths
	Shader(const char* vertexPath, const char* fragmentPath);

	// use/activate shader
	void Use();

	// utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

};
#endif // !SHADER_H
