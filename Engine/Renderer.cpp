#include "EnginePCH.h"
#include "Renderer.h"

#include "OpenGLRenderEngine.h"

namespace GameEngine {

	Renderer::Renderer()
	{
		engine_type = RenderEngines::None;
		_instance = nullptr;
	}

	Renderer::Renderer(RenderEngines EngineType)
	{
		engine_type = EngineType;
		_instance = nullptr;

		switch (engine_type)
		{
		case GameEngine::None:
			_instance = nullptr;
			return;
			break;
		case GameEngine::OpenGL:
			_instance = std::make_shared<OpenGLRenderEngine>();
			break;
		case GameEngine::DirectX:
			break;
		default:
			break;
		}
	}

	Renderer::~Renderer()
	{

	}
}