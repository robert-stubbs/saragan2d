#ifndef _OPENGL_GUI_PLATFORM_H_
#define _OPENGL_GUI_PLATFORM_H_

#include "Types.h"
#include "GUIPlatform.h"

namespace GameEngine
{
	class OpenGLGUIPlatform : public GUIPlatform
	{
	public:
		OpenGLGUIPlatform() {};
		~OpenGLGUIPlatform();

		virtual void Init() override;

		virtual void DemoTest() override;

		virtual void NewScene(float dt) override;
		virtual void EndAndRender() override;

		virtual void Begin(std::string name) override;
		virtual void End() override;

		virtual void BeginChild(std::string name) override;
		virtual void EndChild() override;

		virtual void ResizeWindow(int width, int height) override;

		virtual void KeyDown(int Key);
		virtual void KeyUp(int Key);
		virtual void MouseDown(int button);
		virtual void MouseUp(int button);
		virtual void MouseMove(float x, float y);
		virtual void AddChar(unsigned int c, bool UTF16 = false);
	};
}

#endif