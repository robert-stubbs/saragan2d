#ifndef _CONTEXT_WINDOWS_H_
#define _CONTEXT_WINDOWS_H_

#include "ContextPlatform.h"

namespace GameEngine
{

#define CLASSNAME L"ENGINE"
#define WNDNAME L"ENGINE"

	class ContextWindows: public ContextPlatform
	{
		private:
			HWND hWnd;
			HINSTANCE hInst;
			WNDCLASSEX wc;

			DWORD dStyle;
			DWORD dXStyle;

			PIXELFORMATDESCRIPTOR pfd;
			HGLRC hRC;
			HDC hDC;
			GLuint PixelFormat = 0;

		public:
			ContextWindows();
			~ContextWindows();

			virtual void* GetWindowHandle() override;

			virtual bool InitWindow(int width, int height, std::string window_name, bool fullscreen = false) override;
			virtual bool InitContext() override;

			static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	};
}

#endif