#include"ResourceManager.h"
#include<iostream>
#include "C:/OpenGL/Second-Project/res/stb_image.h"
ResourceManager::ResourceManager(const std::string& cppPath) {
	size_t found = cppPath.find_last_of("/\\");
	mainPath = cppPath.substr(0, found);
}

unsigned char* ResourceManager::load_texture(const std::string& RelPath, int& width, int& height, int& channel)
{
	std::string Path = mainPath + "/" + RelPath;
	std::cerr << "Path " << mainPath << std::endl;
	return stbi_load(Path.c_str(),&width, &height, &channel, 0);
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

