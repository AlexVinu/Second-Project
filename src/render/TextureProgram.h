#pragma once
#include <glad/glad.h>
#include "C:/OpenGL/Second-Project/res/stb_image.h"
#include<string>

class Texture {
public:
	Texture(const std::string &Path);
	GLuint Give_ID() { return texture_ID; }
	bool Is_image_load() { return is_image_load; }
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char* image;
private:
	GLuint texture_ID = 0;
	bool is_image_load;
};