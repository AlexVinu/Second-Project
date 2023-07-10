#pragma once
#include<fstream>
#include<sstream>
#include <map>
#include<memory>
#include"../render/ShaderProgram.h"


class ResourceManager {
public:
	ResourceManager(const std::string& cppPath);

	unsigned char* load_texture(const std::string& RelPath, int& width, int& height, int& channel);
	std::string getfileString(std::string name, const std::string& RelPath);
	std::shared_ptr<Renderer::ShaderProgram> load_shader(std::string ShaderProgramName, const std::string& RelPathVertex, const std::string& RelPathFragment);
private:
	std::string mainPath;
	typedef std::map <std::string, std::shared_ptr<Renderer::ShaderProgram>> shadermap;
	shadermap shaderMaps;
};