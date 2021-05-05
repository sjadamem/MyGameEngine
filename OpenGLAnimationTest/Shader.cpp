#include "Shader.h"

using namespace std;

Shader::Shader(const char * vertexShaderPath, const char * fragmentShaderPath)
{
	string vertexShaderCode, fragmentShaderCode;
	ifstream vShaderFile, fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragmentShaderPath);
		stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexShaderCode = vShaderStream.str();
		fragmentShaderCode = fShaderStream.str();
	}
	catch (ifstream::failure& e)
	{
		cout << "ERROR::SHADER::Cannot read shader" << endl;
	}

	const char* vertexCode = vertexShaderCode.c_str();
	const char* fragmentCode = fragmentShaderCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(this->shaderID);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(this->shaderID);

	this->shaderID = glCreateProgram();
	glAttachShader(this->shaderID, vertex);
	glAttachShader(this->shaderID, fragment);
	glLinkProgram(this->shaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::checkCompileSucces(const std::string type)
{
	int success;
	char infoLog[1024];

	if (type == "PROGRAM")
	{
		glGetProgramiv(this->shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->shaderID, 1024, NULL, infoLog);
			cout << "ERROR::PROGRAM::Linking error | TYPE: " << type << "\n" << infoLog << endl;
		}
	}
	else
	{
		glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(this->shaderID, 1024, NULL, infoLog);
			cout << "ERROR::SHADER::Compiling error | TYPE: " << type << "\n" << infoLog << endl;
		}
	}
}