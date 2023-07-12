#include "vbo.h"
#include<iostream>

GLfloat points[] = {
	0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Верхний правый
	 0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Нижний правый
	-0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Нижний левый
	-0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Верхний левый
};


Buffers::VertexBufferObject::VertexBufferObject()
{

	glGenBuffers(1, &vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLint succes;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_BINDING, &succes);
	if (!succes) {
		std::cerr << "Problems in vbo\n";
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));

}
