#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Buffers {
	class VertexBufferObject {
	public:
		VertexBufferObject();
		VertexBufferObject(const VertexBufferObject&) = delete;
		VertexBufferObject(VertexBufferObject&&) = delete;


		~VertexBufferObject() {
			vertex_vbo = 0;
		}
	private:
		GLuint vertex_vbo = 0;
	};
}