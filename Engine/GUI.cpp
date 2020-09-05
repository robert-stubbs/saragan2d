#include "EnginePCH.h"
#include "GUI.h"
#include "OpenGLGUIPlatform.h"

namespace GameEngine
{
	GUI* GUI::_gui = nullptr;

	GUI::GUI()
	{
		engine_type = RenderEngines::None;
		_instance = nullptr;
		_gui = this;
	}

	GUI::GUI(RenderEngines EngineType)
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
			_instance = std::make_shared<OpenGLGUIPlatform>();
			break;
		case GameEngine::DirectX:
			break;
		default:
			break;
		}
		_gui = this;
	}
}