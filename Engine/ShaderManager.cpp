#include "EnginePCH.h"
#include "ShaderManager.h"
#include "OpenGLShader.h"

namespace GameEngine {

	ShaderManager::ShaderManager()
	{
		_shaders = std::map<std::string, std::shared_ptr<Shader>>();
		engine_type = RenderEngines::None;
		_instance = nullptr;
	}

	ShaderManager::ShaderManager(RenderEngines EngineType)
	{
		_shaders = std::map<std::string, std::shared_ptr<Shader>>();
		engine_type = EngineType;
		_instance = nullptr;

	}

	Shader& ShaderManager::CreateShaderSpace(std::string name)
	{
		switch (engine_type)
		{
		case GameEngine::None:
			break;
		case GameEngine::OpenGL:
			_shaders[name] = std::make_shared<OpenGLShader>();
			break;
		case GameEngine::DirectX:
			break;
		default:
			break;
		}
		
		_instance = _shaders[name];

		return *(_shaders[name]);
	}

	Shader& ShaderManager::operator[](std::string name)
	{
		return *(_shaders[name]);
	}

	Shader& ShaderManager::BindNewShader(std::string name)
	{
		if (_instance != nullptr) {
			_instance->unbind();
			_instance = nullptr;
		}

		_instance = _shaders[name];
		_instance->bind();

		return *_instance;
	}

	ShaderManager::~ShaderManager()
	{

	}


	void ShaderManager::BindShaderStructure()
	{
		if (_instance != nullptr) {
			_instance->BindShaderStructure();
		}
	}
}