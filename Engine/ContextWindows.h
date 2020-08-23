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
			WNDCLASSEX wc = { };

			bool usePerformanceCounter;
			double offset;
			double frequency;

			DWORD dStyle = WS_OVERLAPPEDWINDOW;
			DWORD dXStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

			PIXELFORMATDESCRIPTOR pfd;
			GLuint PixelFormat = 0;

		public:
			HGLRC hRC;
			HDC hDC;
			ContextWindows();
			~ContextWindows();

			virtual void* GetWindowHandle() override;

			virtual bool InitWindow(int width, int height, std::string window_name, bool fullscreen = false) override;
			virtual bool InitContext() override;
			virtual void SwapContextBuffers() override;
			virtual double GetTime() override;
			virtual double GetSystemTime();
			virtual double GetSystemFrequency();

			static LRESULT CALLBACK WndProcRouter(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
			LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	};
}

#endif