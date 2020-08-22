#ifndef _INPUT_GLFW_H_
#define _INPUT_GLFW_H_

#include "InputPlatform.h"

namespace GameEngine
{
	class InputGLFW : public InputPlatform
	{
	public:
		InputGLFW();

		virtual bool IsKeyPressed(int key);

		virtual bool IsMouseButtonPressed(int button);

		virtual std::pair<float, float> GetMousePos();

		virtual int GetKey(int keycode);
	};
}

#endif