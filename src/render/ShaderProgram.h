#pragma once
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader);

		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram(ShaderProgram&&) = delete;

		void use_ShaderProgram() { glUseProgram(this->ID_ShaderProgram); }
		bool IsCompiled() const { return m_IsCompiled; }
		GLuint Give_Id()const  { return ID_ShaderProgram; }
		ShaderProgram::~ShaderProgram()
		{
			glDeleteProgram(ID_ShaderProgram);
			ID_ShaderProgram = 0;
		}

	private:
		bool CreateShader(const std::string& shader, GLuint &ID, GLenum typeOfShader);
		GLuint ID_ShaderProgram = 0;
		bool m_IsCompiled = false;
	};
}