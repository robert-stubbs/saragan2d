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

		virtual void DemoTest(float dt) override;
	};
}

#endif