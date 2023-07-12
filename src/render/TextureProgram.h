#pragma once
#include <glad/glad.h>

class Texture {
public:
	Texture();
	GLuint Give_ID() { return texture_ID; }
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char* image;
private:
	GLuint texture_ID = 0;
};