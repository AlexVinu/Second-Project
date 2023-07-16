#pragma once
#include<fstream>
#include<sstream>
#include <map>
#include<memory>
#include"../render/ShaderProgram.h"
#include"../render/TextureProgram.h"

class ResourceManager {
public:
	ResourceManager(const std::string& cppPath);

	void getObjects_Textures();
	void getObjects_Shaders();

	std::shared_ptr<Texture> load_texture(std::string texturename, const std::string& RelPath);
	std::string getfileString(std::string name, const std::string& RelPath);
	std::shared_ptr<Renderer::ShaderProgram> load_shader(std::string ShaderProgramName, const std::string& RelPathVertex, const std::string& RelPathFragment);
private:
	std::string mainPath;

	typedef std::map <std::string, std::shared_ptr<Renderer::ShaderProgram>> shadermap;
	shadermap shaderMaps;
	typedef std::map<std::string, std::shared_ptr<Texture>> texturemap;
	texturemap textureMap;
};