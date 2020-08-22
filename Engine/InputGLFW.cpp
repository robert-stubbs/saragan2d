#include "EnginePCH.h"
#include "InputGLFW.h"

#include "Engine.h"

namespace GameEngine
{
	InputGLFW::InputGLFW() : InputPlatform()
	{

	}

	bool InputGLFW::IsKeyPressed(int key)
	{
		GLFWwindow* window = Engine::get().window;
		int val = glfwGetKey(window, key);

		return val == GLFW_PRESS || val == GLFW_REPEAT;
	}

	bool InputGLFW::IsMouseButtonPressed(int button)
	{
		GLFWwindow* window = Engine::get().window;
		int val = glfwGetMouseButton(window, button);

		return val == GLFW_PRESS || val == GLFW_REPEAT;
	}

	std::pair<float, float> InputGLFW::GetMousePos()
	{
		GLFWwindow* window = Engine::get().window;

		double x;
		double y;

		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}

	int InputGLFW::GetKey(int keycode)
	{
		return keycode;
	}

}