#include "EnginePCH.h"
#include "Renderer.h"

#include "OpenGLRenderEngine.h"

namespace GameEngine {

	Renderer::Renderer()
	{
		engine_type = RenderEngines::None;
		render_engine = nullptr;
	}

	Renderer::Renderer(RenderEngines EngineType)
	{
		engine_type = EngineType;
		render_engine = nullptr;

		switch (engine_type)
		{
		case GameEngine::None:
			render_engine = nullptr;
			return;
			break;
		case GameEngine::OpenGL:
			render_engine = std::make_shared<OpenGLRenderEngine>();
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