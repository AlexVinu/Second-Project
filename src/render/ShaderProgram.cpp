#include "ShaderProgram.h"

namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader)
	{
		GLuint vs;
		if (!CreateShader(vertex_shader, vs, GL_VERTEX_SHADER)) {
			std::cerr << "Can`t create vertex shader\n";
		}
		GLuint fs;
		if (!CreateShader(fragment_shader, fs, GL_FRAGMENT_SHADER)) {
			std::cerr << "Can`t create fragment shader\n";
		}
		ID_ShaderProgram = glCreateProgram();
		glAttachShader(ID_ShaderProgram, vs);
		glAttachShader(ID_ShaderProgram, fs);
		glLinkProgram(ID_ShaderProgram);

		GLint succes;
		glGetProgramiv(ID_ShaderProgram, GL_LINK_STATUS, &succes);
		if (!succes) {
			std::cerr << "Can`t link program\n";
		}
		m_IsCompiled = true;
		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	bool ShaderProgram::CreateShader(const std::string &shader, GLuint &ID, GLenum typeOfShader)
	{
		GLint succes;
		const char* shaderChar = shader.c_str();
		ID = glCreateShader(typeOfShader);
		glShaderSource(ID, 1, &shaderChar, nullptr);
		glCompileShader(ID);

		glGetShaderiv(ID, GL_COMPILE_STATUS, &succes);
		if (!succes) {
			return false;
		}
		return true;
	}
	void ShaderProgram::setVec3f(std::string NameOfUniform, float x, float y, float z){glUniform3f(glGetUniformLocation(this->Give_Id(), NameOfUniform.c_str()), x, y, z);}
	void ShaderProgram::setVec1f(std::string NameOfUniform, float x){glUniform1f(glGetUniformLocation(this->Give_Id(), NameOfUniform.c_str()), x);}
}