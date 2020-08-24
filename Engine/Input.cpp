#include "EnginePCH.h"
#include "Input.h"
#include "InputGLFW.h"
#include "InputWindows.h"

namespace GameEngine
{
	Input Input::_input = Input();

	void Input::SetPlatform(PLATFORM platform)
	{
		switch (platform)
		{
			case GameEngine::PLATFORM::WINDOWS:
				_instance = std::make_shared<InputWindows>();
				break;
			case GameEngine::PLATFORM::GLFW:
				_instance = std::make_shared<InputGLFW>();
				break;
			case GameEngine::PLATFORM::LINUX:
				break;
			case GameEngine::PLATFORM::MAC:
				break;
			default:
				break;
		}
	}
}