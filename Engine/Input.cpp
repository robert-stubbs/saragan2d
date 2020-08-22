#include "EnginePCH.h"
#include "Input.h"
#include "InputGLFW.h"
#include "InputWindows.h"

namespace GameEngine
{
	Input Input::_Instance = Input();

	void Input::SetPlatform(PLATFORM platform)
	{
		switch (platform)
		{
			case GameEngine::PLATFORM::WINDOWS:
				_platform = new InputWindows();
				break;
			case GameEngine::PLATFORM::GLFW:
				_platform = new InputGLFW();
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