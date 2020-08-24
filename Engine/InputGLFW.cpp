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
		GLFWwindow* window = (GLFWwindow *)(Engine::getContext().Get().GetWindowHandle());
		int val = glfwGetKey(window, key);

		return val == GLFW_PRESS || val == GLFW_REPEAT;
	}

	bool InputGLFW::IsMouseButtonPressed(int button)
	{
		GLFWwindow* window = (GLFWwindow*)(Engine::getContext().Get().GetWindowHandle());
		int val = glfwGetMouseButton(window, button);

		return val == GLFW_PRESS || val == GLFW_REPEAT;
	}

	std::pair<float, float> InputGLFW::GetMousePos()
	{
		GLFWwindow* window = (GLFWwindow*)(Engine::getContext().Get().GetWindowHandle());

		double x;
		double y;

		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}

	int InputGLFW::GetKey(int keycode)
	{
		return keycode;
	}

	int InputGLFW::GetPlatformKey(int keycode)
	{
		return keycode;
	}

}