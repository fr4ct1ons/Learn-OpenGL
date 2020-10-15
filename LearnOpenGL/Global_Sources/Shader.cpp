#include"Shader.h"

Shader::Shader(std::string vertexProgramPath, std::string fragmentProgramPath, std::string newName)
{
	std::string vertexCode, fragmentCode;

	std::ifstream vertexFile, fragmentFile;

	name = newName;

	try
	{
		vertexFile.open(vertexProgramPath);
		fragmentFile.open(fragmentProgramPath);

		if (!fragmentFile.good())
		{
			std::cout << "ERROR LOADING SHADERS FOR " << name << " - Invalid fragment shader file. " << "\n";
			std::cout << "Stopping shader compilation." << std::endl;
			return;
		}

		if (!vertexFile.good())
		{
			std::cout << "ERROR LOADING SHADERS FOR " << name << " - Invalid vertex shader file. " << "\n";
			std::cout << "Stopping shader compilation." << std::endl;
			return;
		}

		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		std::cout << fragmentStream.str() << std::endl;

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR LOADING SHADERS FOR " << name << " - File not opened correctly. Error: " << e.what() << "\n";
		std::cout << "Stopping shader compilation." << std::endl;
		return;
	}

	int success; 
	char infoLog[1024];

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (success == 0)
	{
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		std::cout << "ERROR COMPILING FRAGMENT SHADER FOR " << name << "! Error log: \n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (success == 0)
	{
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		std::cout << "ERROR COMPILING VERTEX SHADER FOR " << name << "! Error log: \n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infoLog);
		std::cout << "ERROR LINKING SHADER PROGRAM FOR " << name << "! Error log: \n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//std::cout << vertexCode << std::endl;
	//std::cout << fragmentCode << std::endl;
}

Shader::Shader()
{
	ID = -1;
}

void Shader::SetAsCurrent()
{
	if (ID <= 0)
	{

	}
	glUseProgram(ID);
}