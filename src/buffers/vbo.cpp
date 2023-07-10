#include "vbo.h"
#include<iostream>

GLfloat points[] = {
	0.0, 1.0, 0.0,		1.0, 0.0, 0.0,		0.0, 0.0,
	1.0, -1.0, 0.0,		0.0, 1.0, 0.0,		1.0, 0.0,
	-1.0, -1.0, 0.0,	0.0, 0.0, 1.0,		0.5 ,1.0,
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

}
