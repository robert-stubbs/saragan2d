#include "EnginePCH.h"
#include "ShaderManager.h"
#include "OpenGLShader.h"

namespace GameEngine {

	ShaderManager::ShaderManager()
	{
		_shaders = std::map<std::string, std::shared_ptr<Shader>>();
		engine_type = RenderEngines::None;
		current_shader = nullptr;
	}

	ShaderManager::ShaderManager(RenderEngines EngineType)
	{
		_shaders = std::map<std::string, std::shared_ptr<Shader>>();
		engine_type = EngineType;
		current_shader = nullptr;

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
		
		current_shader = _shaders[name];

		return *(_shaders[name]);
	}

	Shader& ShaderManager::operator[](std::string name)
	{
		return *(_shaders[name]);
	}

	Shader& ShaderManager::BindNewShader(std::string name)
	{
		if (current_shader != nullptr) {
			current_shader->unbind();
			current_shader = nullptr;
		}

		current_shader = _shaders[name];
		current_shader->bind();

		return *current_shader;
	}

	ShaderManager::~ShaderManager()
	{

	}
}