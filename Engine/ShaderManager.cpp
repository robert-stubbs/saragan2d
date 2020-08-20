#include "EnginePCH.h"
#include "ShaderManager.h"


namespace GameEngine {

	ShaderManager::ShaderManager()
	{
		engine_type = RenderEngines::None;
		//shader_engine = nullptr;
	}

	ShaderManager::ShaderManager(RenderEngines EngineType)
	{
		engine_type = EngineType;
		//shader_engine = nullptr;

		//switch (engine_type)
		//{
		//case GameEngine::None:
		//	render_engine = nullptr;
		//	return;
		//	break;
		//case GameEngine::OpenGL:
		//	render_engine = std::make_shared<OpenGLRenderEngine>();
		//	break;
		//case GameEngine::DirectX:
		//	break;
		//default:
		//	break;
		//}
	}

	ShaderManager::~ShaderManager()
	{

	}
}