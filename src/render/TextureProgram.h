#pragma once
#include <glad/glad.h>
#include<string>

class Texture {
public:
	Texture(const std::string &Path);
	GLuint Give_ID() { return texture_ID; }
	bool Is_image_load() { return is_image_load; }
	~Texture() { texture_ID = 0; }
private:
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char* image;
	GLuint texture_ID = 0;
	bool is_image_load;
};