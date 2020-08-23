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
		glfwTerminate();
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

		glfwSetWindowUserPointer(window, this);
		
		glfwSetKeyCallback(window, ContextGLFW::static_key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		// do mouse callback as well
		//glfwSetCursorPosCallback && glfwSetMouseCallback

		Engine::getRenderer().Init();

		return true;
	}

	void ContextGLFW::RenderLoop()
	{
		double lastTime = Engine::getContext().GetWindow().GetTime();
		double timer = lastTime;
		double deltaTime = 0;
		double nowTime = 0;
		int frames = 0;
		int updates = 0;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
		    // - Measure time
		    nowTime = glfwGetTime();
		    deltaTime += (nowTime - lastTime) / limitFPS;
		    lastTime = nowTime;

		    // - Only update at 60 frames / s
		    while (deltaTime >= 1.0) {
		        Engine::get().Update((float)deltaTime);
		        updates++;
		        deltaTime--;
		    }

			Engine::get().Render();

		    frames++;

		    // - Reset after one second
		    if (glfwGetTime() - timer > 1.0) {
		        timer++;
		        std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
		        updates = 0, frames = 0;
		    }
		}
	}
	
	void ContextGLFW::SwapContextBuffers()
	{
		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	double ContextGLFW::GetTime()
	{
		return glfwGetTime();
	}


	void ContextGLFW::static_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		ContextGLFW* windowManager = static_cast<ContextGLFW*>(glfwGetWindowUserPointer(window));
		return windowManager->key_callback(window, key, scancode, action, mods);
	}

	void ContextGLFW::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{	
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			return Engine::get().KeyDown(key);
		}
		else if (action == GLFW_RELEASE) {

			return Engine::get().KeyUp(key);
		}
	}



	void ContextGLFW::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		ContextGLFW* windowManager = static_cast<ContextGLFW*>(glfwGetWindowUserPointer(window));
		return windowManager->cursor_callback(window, xpos, ypos);

	}

	void ContextGLFW::cursor_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Engine::get().MouseMove((float)xpos, (float)ypos);
	}
}