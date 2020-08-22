#include "EnginePCH.h"
#include "ContextGLFW.h"
#include "Engine.h"

namespace GameEngine
{
	ContextGLFW::ContextGLFW() : ContextPlatform()
	{

	}

	ContextGLFW::~ContextGLFW()
	{

	}

	void* ContextGLFW::GetWindowHandle()
	{
		return window;
	}

	bool ContextGLFW::InitWindow(int width, int height, std::string window_name, bool fullscreen)
	{
		_window_name = window_name;
		_fullscreen = fullscreen;
		_window_width = width;
		_window_height = height;

		if (!glfwInit()) {
			return false;
		}

		if (_fullscreen) {
			window = glfwCreateWindow(_window_width, _window_height, _window_name.c_str(), glfwGetPrimaryMonitor(), NULL);
		}
		else {
			/* Create a windowed mode window and its OpenGL context */
			window = glfwCreateWindow(_window_width, _window_height, _window_name.c_str(), NULL, NULL);
		}

		if (!window)
		{
			glfwTerminate();
			return false;
		}

		return true;
	}

	bool ContextGLFW::InitContext()
	{
		glfwMakeContextCurrent(window);

		Engine::getRenderer().Init();

		return true;
	}
}