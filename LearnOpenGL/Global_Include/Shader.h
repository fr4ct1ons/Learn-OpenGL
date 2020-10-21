#pragma once
#include"glad/glad.h"
#include<iostream>
#include <fstream>
#include <sstream>

#include"glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"glm/mat4x4.hpp"

class Shader
{
private:
	unsigned int ID;
	std::string name;

public:
	Shader(std::string vertexProgramPath, std::string fragmentProgramPath, std::string newName);
	void SetAsCurrent();
	Shader();

	void SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void SetMatrix(const std::string& name, glm::mat4 value)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
};