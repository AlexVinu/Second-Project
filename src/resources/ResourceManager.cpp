#include"ResourceManager.h"
#include<iostream>
#include "C:/OpenGL/Second-Project/res/stb_image.h"

ResourceManager::ResourceManager(const std::string& cppPath) {
	size_t found = cppPath.find_last_of("/\\");
	mainPath = cppPath.substr(0, found);
}

std::shared_ptr<Texture> ResourceManager::load_texture(std::string texturename, const std::string& RelPath)
{
	Texture textureObj;
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(textureObj);
	std::string Path = mainPath + "/" + RelPath;
	texture->image = stbi_load(Path.c_str(),&texture->width, &texture->height, &texture->channels, 0);
	if (!texture->image) {
		std::cerr << "loading textures failed\n";
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->image);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(texture->image);
	glBindBuffer(GL_TEXTURE_2D, 0);
	textureMap.insert(std::pair(texturename, texture));
	return texture;
}

std::string ResourceManager::getfileString(std::string name, const std::string& RelPath)
{
	std::ifstream File;
	File.open(mainPath + "/" + RelPath.c_str(), std::ios::in | std::ios::binary);
	if (!File.is_open()) {
		std::cerr << "File of" << name << " didn`t open\n";
		return {};
	}
	std::stringstream rbuffer;
	rbuffer << File.rdbuf();
	return rbuffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::load_shader(std::string ShaderProgramName, const std::string& RelPathVertex, const std::string& RelPathFragment)
{
	std::string Vertex = getfileString("VertexShader", RelPathVertex);
	std::string Fragment = getfileString("FragmentShader", RelPathFragment);
	std::shared_ptr<Renderer::ShaderProgram> &ShaderProgram = shaderMaps.emplace(ShaderProgramName, std::make_shared<Renderer::ShaderProgram>(Vertex, Fragment)).first->second;
	if (ShaderProgram->IsCompiled())
	{
		return ShaderProgram;
	}
	else
	{
		std::cerr << "Can`t load shader program" << std::endl << "Vertex shader in path: " << RelPathVertex << std::endl << "fragment shader in path: " << RelPathFragment << std::endl;
		return nullptr;
	}
}

