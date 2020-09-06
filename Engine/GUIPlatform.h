#ifndef _GUI_PLATFORM_H_
#define _GUI_PLATFORM_H_

#include "Types.h"

namespace GameEngine
{
	class GUIPlatform
	{
	public:
		GUIPlatform() {};

		virtual void Init() = 0;

		virtual void DemoTest(float dt) = 0;

		virtual void NewScene(float dt) = 0;
		virtual void EndAndRender() = 0;

		virtual void Begin(std::string name) = 0;
		virtual void End() = 0;

		virtual void BeginChild(std::string name) = 0;
		virtual void EndChild() = 0;

		virtual void ResizeWindow(int width, int height) = 0;

		virtual void KeyDown(int Key) = 0;
		virtual void KeyUp(int Key) = 0;
		virtual void MouseDown(int button) = 0;
		virtual void MouseUp(int button) = 0;
		virtual void MouseMove(float x, float y) = 0;
		virtual void AddChar(unsigned int c, bool UTF16) = 0;
	};
}

#endif