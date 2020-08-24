#include "EnginePCH.h"
#include "Context.h"

#include "ContextGLFW.h"
#include "ContextPlatform.h"
#include "ContextWindows.h"

namespace GameEngine {
	
	void Context::SetPlatform(PLATFORM platform)
	{
		switch (platform)
		{
		case GameEngine::PLATFORM::WINDOWS:
			_instance = std::make_shared<ContextWindows>();
			break;
		case GameEngine::PLATFORM::GLFW:
			_instance = std::make_shared<ContextGLFW>();
			break;
		case GameEngine::PLATFORM::LINUX:
			break;
		case GameEngine::PLATFORM::MAC:
			break;
		default:
			break;
		}
	}

	bool Context::InitWindow(int width, int height, std::string window_name, bool fullscreen)
	{
		return _instance->InitWindow(width, height, window_name, fullscreen);
	}

	bool Context::InitContext()
	{
		return _instance->InitContext();
	}

	void Context::SwapContextBuffers()
	{
		return _instance->SwapContextBuffers();
	}
}