#include "EnginePCH.h"
#include "ContextWindows.h"
#include "Engine.h"

//https://elcharolin.wordpress.com/2015/01/24/wndproc-as-a-class-member-win32/

namespace GameEngine
{
	ContextWindows::ContextWindows() : ContextPlatform()
	{
		hInst = NULL;
		hWnd = NULL;
		usePerformanceCounter = false;
		offset = -1;
	}

	ContextWindows::~ContextWindows()
	{

	}

	void* ContextWindows::GetWindowHandle()
	{
		return hWnd;
	}

	bool ContextWindows::InitWindow(int width, int height, std::string window_name, bool fullscreen)
	{
		_window_name = window_name;
		_fullscreen = fullscreen;
		_window_width = width;
		_window_height = height;


		wc = { };

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
		wc.lpfnWndProc = &WndProcRouter;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(0);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wc.lpszMenuName = NULL;
		wc.lpszClassName = CLASSNAME;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		RegisterClassEx(&wc);

		if (_fullscreen)
		{

			DEVMODE dmScreenSettings;                   // Device Mode
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));       // Makes Sure Memory's Cleared
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);       // Size Of The Devmode Structure
			dmScreenSettings.dmPelsWidth = _window_width;            // Selected Screen Width
			dmScreenSettings.dmPelsHeight = _window_height;           // Selected Screen Height
			dmScreenSettings.dmBitsPerPel = 24;             // Selected Bits Per Pixel
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", L"Saragan", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
				{
					_fullscreen = false;
				}
				else {
					MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
					return false;
				}
			}

			dXStyle = WS_EX_APPWINDOW;
			dStyle = WS_POPUP;
			ShowCursor(FALSE);
		}

		hWnd = CreateWindowEx(dXStyle, CLASSNAME, WNDNAME, dStyle, 0, 0, _window_width, _window_height, NULL, NULL, GetModuleHandle(0), this);

		if (hWnd == NULL)
		{
			std::cout << GetLastError() << std::endl;
			MessageBox(NULL, TEXT("Create Window Failed!"), TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		return true;
	}

	bool ContextWindows::InitContext()
	{
		pfd =												// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),                  // Size Of This Pixel Format Descriptor
			1,												// Version Number
			PFD_DRAW_TO_WINDOW |							// Format Must Support Window
			PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,								// Must Support Double Buffering
			PFD_TYPE_RGBA,									// Request An RGBA Format
			24,												// Select Our Color Depth
			0, 0, 0, 0, 0, 0,								// Color Bits Ignored
			0,												// No Alpha Buffer
			0,												// Shift Bit Ignored
			0,												// No Accumulation Buffer
			0, 0, 0, 0,										// Accumulation Bits Ignored
			32,												// 16Bit Z-Buffer (Depth Buffer)
			0,												// No Stencil Buffer
			0,												// No Auxiliary Buffer
			PFD_MAIN_PLANE,									// Main Drawing Layer
			0,												// Reserved
			0, 0, 0											// Layer Masks Ignored
		};
		PixelFormat = 0;

		// generate new context, sore in map
		if (!(hDC = GetDC(hWnd)))                         // Did We Get A Device Context?
		{		
			std::cout << "#### Can't Create A GL Device Context ####" << std::endl;
			return false;								 // Return FALSE
		}

		if (!pfd.dwFlags || PixelFormat == 0)
		{
			if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
			{
				std::cout << "#### Can't Find A Suitable PixelFormat ####" << std::endl;
				return false;
			}
		}


		if (SetPixelFormat(hDC, PixelFormat, &pfd) == FALSE)
		{
			std::cout << "#### SetPixelFormat failed ####" << std::endl;
			return false;
		}

		Engine::getRenderer().SetCurrentContext(hRC, hDC);

		frequency = GetSystemFrequency();
		if (offset == -1) { offset = GetSystemTime(); }

		if (ShowWindow(hWnd, true) && UpdateWindow(hWnd))
		{
			return true;
		}	

		return false;
	}

	void ContextWindows::RenderLoop()
	{
		double lastTime = GetTime();
		double timer = lastTime;
		double deltaTime = 0;
		double nowTime = 0;
		int frames = 0;
		int updates = 0;

		double dt = 0.15;
		MSG msg = { 0 };

		while (WM_QUIT != msg.message)
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// - Measure time

			nowTime = GetTime();
			deltaTime += (nowTime - lastTime) / limitFPS;
			lastTime = nowTime;

			// - Only update at 60 frames / s
			while (deltaTime >= 1.0) {
				Engine::get().Update((float)deltaTime);
				updates++;
				deltaTime--;
			}

			Engine::get().Render();

			frames++;

			// - Reset after one second
			if (GetTime() - timer > 1.0) {
				timer++;
				std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
				updates = 0, frames = 0;
			}
		}
	}

	void ContextWindows::SwapContextBuffers()
	{
		SwapBuffers(hDC);
	}

	double ContextWindows::GetTime()
	{
		double st = GetSystemTime();
		double fq = GetSystemFrequency();

		double val = (double)(st - offset) / fq;

		return val;
	}

	double ContextWindows::GetSystemTime()
	{
		if (usePerformanceCounter) {
			LARGE_INTEGER value;
			QueryPerformanceCounter((LARGE_INTEGER*)&value);
			return (double)value.QuadPart;
		}

		return (double)timeGetTime();
	}

	double ContextWindows::GetSystemFrequency()
	{
		LARGE_INTEGER freq;
		if (QueryPerformanceFrequency((LARGE_INTEGER*)&freq))
		{
			usePerformanceCounter = true;
			return (double)freq.QuadPart;
		}

		return 1000;
	}

	LRESULT CALLBACK ContextWindows::WndProcRouter(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		ContextWindows* app;

		if (Msg == WM_CREATE)
		{
			app = (ContextWindows*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)app);
		}
		else {
			app = (ContextWindows*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}
		return app->WndProc(hWnd, Msg, wParam, lParam);
	}

	LRESULT CALLBACK ContextWindows::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{

		switch (Msg)
		{
			case WM_KEYDOWN:
			{
				Engine::get().KeyDown(Input::Get().GetPlatformKey((int)wParam));
			}
			break;

			case WM_KEYUP:
			{
				Engine::get().KeyUp(Input::Get().GetPlatformKey((int)wParam));
			}
			break;

			case WM_LBUTTONDOWN:
			{
			} break;
			case WM_LBUTTONUP:
			{
				//Engine::getEngine().MouseUp(Msg, wParam, lParam);
			} break;
			case WM_RBUTTONDOWN:
			{
				//Engine::getEngine().MouseDown(Msg, wParam, lParam);
			} break;
			case WM_RBUTTONUP:
			{
				//Engine::getEngine().MouseUp(Msg, wParam, lParam);
			} break;
			case WM_MOUSEMOVE:
			{
				//Engine::getEngine().MouseMove(Msg, wParam, lParam);
			} break;
			case WM_SIZE:
			{
				//Resize The OpenGL Window
				if (wglGetCurrentDC() && wglGetCurrentContext())
				{
					//Engine::getEngine().ResizeWindow(LOWORD(lParam), HIWORD(lParam));
				}
			} break;
			case WM_CLOSE:
			{
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			} break;
			case WM_DESTROY:
			{
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			} break;
			default:
				return DefWindowProc(hWnd, Msg, wParam, lParam);
		}

		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
}