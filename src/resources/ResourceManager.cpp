#include"ResourceManager.h"
#include<iostream>

ResourceManager::ResourceManager(const std::string& cppPath) {
	size_t found = cppPath.find_last_of("/\\");
	mainPath = cppPath.substr(0, found);
}

void ResourceManager::getObjects_Textures()
{
	std::map<std::string, std::shared_ptr<Texture>>::iterator iter = textureMap.begin();
	while (iter != textureMap.end()) {
		std::cerr << "texture " << iter->first << " with id " << iter->second->Give_ID()<<std::endl;
		iter++;
	}
}

void ResourceManager::getObjects_Shaders()
{
	std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>>::iterator iter = shaderMaps.begin();
	while (iter != shaderMaps.end()) {
		std::cerr << "shader " << iter->first << " with id " << iter->second->Give_Id() << std::endl;
		iter++;
	}
}

std::shared_ptr<Texture> ResourceManager::load_texture(std::string texturename, const std::string& RelPath)
{
	std::string Path = mainPath + "/" + RelPath;
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(Path);
	if (!texture->Is_image_load()) {
		std::cerr << "loading textures failed\n";
		return nullptr;
	}
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

