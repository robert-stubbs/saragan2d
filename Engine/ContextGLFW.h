#ifndef _CONTEXT_GLFW_H_
#define _CONTEXT_GLFW_H_

#include "ContextPlatform.h"

namespace GameEngine
{
	class ContextGLFW : public ContextPlatform
	{
		private:
			GLFWwindow* window;


		public:
			ContextGLFW();
			~ContextGLFW();

			virtual void* GetWindowHandle() override;

			virtual bool InitWindow(int width, int height, std::string window_name, bool fullscreen = false) override;
			virtual bool InitContext() override;
			virtual void SwapContextBuffers() override;
			virtual double GetTime() override;
	};
}

#endif