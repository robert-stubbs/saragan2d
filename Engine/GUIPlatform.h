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

		virtual void ResizeWindow(int width, int height) = 0;

	};
}

#endif