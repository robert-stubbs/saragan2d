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
		_gui = this;
	}

	void GUI::SetPlatformAndRenderer(PLATFORM platform, RenderEngines engine) {

		engine_type = engine;
		_instance = nullptr;

		if (platform == PLATFORM::GLFW && engine_type == RenderEngines::OpenGL) {
			_instance = std::make_shared<OpenGLGUIPlatform>();
		}
		else {
			_instance = nullptr;
		}
	}
}