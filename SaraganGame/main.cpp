#include "GamePCH.h"
#include "GameLibrary.h"

#include "cCreateWnd.h"
#include "cRegWnd.h"


//https://github.com/HectorPeeters/opengl_premake_boilerplate

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

void PreLoad();
cCreateWnd CreateEngineWindow();
void Load();
void PostLoad();
void Update(float dt);
void Render();
void CleanUp();

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {

	// load up Error logger and instantiate some classes
	PreLoad();

	//create the window
	cCreateWnd Wnd = CreateEngineWindow();

	// Initialise Important stuff before window is shown
	Load();
	Wnd.show(true);
	PostLoad();

	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Update((float)dt);


		Render();
	}

	CleanUp();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_KEYDOWN:
	{
	}break;

	case WM_KEYUP:
	{
	}break;
	case WM_LBUTTONDOWN:
	{
	} break;
	case WM_LBUTTONUP:
	{
	} break;
	case WM_RBUTTONDOWN:
	{
	} break;
	case WM_RBUTTONUP:
	{
	} break;
	case WM_MOUSEMOVE:
	{
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

void PreLoad()
{

}

cCreateWnd CreateEngineWindow()
{
	cRegWnd WinApp(hInst, WndProc, false, 800, 600);
	WinApp.Register();

	cCreateWnd Wnd(&WinApp);
	hWnd = Wnd.Create();

	return Wnd;
}

void Load()
{
}

void PostLoad()
{

}

void Update(float dt)
{
}

void Render()
{
}

void CleanUp()
{
}

