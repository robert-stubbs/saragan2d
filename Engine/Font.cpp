#include "EnginePCH.h"
#include "Font.h"
#include "OpenGLFont.h"

namespace GameEngine
{
	Font Font::_font = Font();

	Font::Font()
	{
		engine_type = RenderEngines::None;
		_instance = nullptr;
		_font = *this;
	}

	Font::Font(RenderEngines EngineType)
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
			_instance = std::make_shared<OpenGLFont>();
			break;
		case GameEngine::DirectX:
			break;
		default:
			break;
		}
	}

	Font::~Font()
	{

	}
}