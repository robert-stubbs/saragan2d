#ifndef _CONTEXT_PLATFORM_H_
#define _CONTEXT_PLATFORM_H_

namespace GameEngine
{
	/*
		going to need a function to get the windows handle/instance/HWND
	
			

	
	*/
	class ContextPlatform
	{
		protected:
			std::string _window_name;
			bool _fullscreen;
			int _window_width;
			int _window_height;

		public:
			ContextPlatform() {};
			~ContextPlatform() {};

			virtual void* GetWindowHandle() = 0;

			virtual bool InitWindow(int width, int height, std::string window_name, bool fullscreen = false) = 0;
			virtual bool InitContext() = 0;
	};
}

#endif