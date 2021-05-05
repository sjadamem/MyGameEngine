#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void Use() { glUseProgram(this->shaderID); }

	void SetBool(const std::string& name, bool value) { glUniform1i(glGetUniformLocation(this->shaderID, name.c_str()), value); }
	void SetInt(const std::string& name, int value) { glUniform1i(glGetUniformLocation(this->shaderID, name.c_str()), value); }
	void SetFloat(const std::string& name, float value) { glUniform1f(glGetUniformLocation(this->shaderID, name.c_str()), value); }
	
	void SetVec2(const std::string& name, const glm::vec2& value) { glUniform2fv(glGetUniformLocation(this->shaderID, name.c_str()), 1, glm::value_ptr(value)); }
	void SetVec3(const std::string& name, const glm::vec3& value) { glUniform3fv(glGetUniformLocation(this->shaderID, name.c_str()), 1, glm::value_ptr(value)); }
	void SetVec4(const std::string& name, const glm::vec4& value) { glUniform4fv(glGetUniformLocation(this->shaderID, name.c_str()), 1, glm::value_ptr(value)); }
//	void SetMat4(const std::string& name, const glm::mat4& value) { glUniformMatrix4fv(glGetUniformLocation(this->shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); }
	void SetMat4(const std::string& name, const glm::mat4& value, unsigned int size = 1, GLboolean transpose = GL_FALSE) { glUniformMatrix4fv(glGetUniformLocation(this->shaderID, name.c_str()), size, transpose, glm::value_ptr(value)); }
	
	/*void SetMat4(const std::string& name, const std::vector<glm::mat4>& value, size_t size = 1, GLboolean transpose = GL_FALSE)
	{
		glUniformMatrix4fv(glGetUniformLocation(this->shaderID, name.c_str()), size, transpose, glm::value_ptr(value[0]));
		return;
	}
	*/

private:
	unsigned int shaderID;

	void checkCompileSucces(const std::string type);
};

#endif