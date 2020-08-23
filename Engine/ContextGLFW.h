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
			virtual void RenderLoop() override;
			virtual void SwapContextBuffers() override;
			virtual double GetTime() override;

			static void static_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

			static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			void cursor_callback(GLFWwindow* window, double xpos, double ypos);
	};
}

#endif