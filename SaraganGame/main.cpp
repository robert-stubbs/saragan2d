#include "GamePCH.h"
#include "GameLibrary.h"

#include "cCreateWnd.h"
#include "cRegWnd.h"
#include "cErrorLogger.h"
#include "Engine.h"

#include "RayState.h"

Engine* pEngine;
RayState* raystate;

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

	double dt = 0.15;
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Update((float)dt);


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
	cErrorLogger::Log().WriteToConsole("#######################################################");
	cErrorLogger::Log().WriteToConsole("> Created Console");

	cErrorLogger::Log().WriteToConsole("> Creating Engine");
	pEngine = new Engine();

	raystate = new RayState();

}

cCreateWnd CreateEngineWindow()
{
	cErrorLogger::Log().WriteToConsole("#######################################################");
	cErrorLogger::Log().WriteToConsole("> Creating Window");

	cRegWnd WinApp(hInst, WndProc, false, 800, 600);
	WinApp.Register();

	cCreateWnd Wnd(&WinApp);
	hWnd = Wnd.Create();

	cErrorLogger::Log().WriteToConsole("#######################################################");

	return Wnd;
}

void Load()
{
	cErrorLogger::Log().WriteToConsole("> Loading Engine\n");
	if (!pEngine->init(hWnd)) {
		cErrorLogger::Log().WriteToConsole("Failed to Initialize OpenGL\n");
		return;
	}

	raystate->Init();
	Engine::getEngine().GameFSM->AddState(raystate, true);
}

void PostLoad()
{
	pEngine->PostInit();
}

void Update(float dt)
{
	pEngine->Update(dt);
	pEngine->UpdateOrth(dt);
}

void Render()
{
	pEngine->render();
	pEngine->renderOrth();
}

void CleanUp()
{
	cErrorLogger::Log().WriteToConsole("#######################################################\n");
	cErrorLogger::Log().WriteToConsole("> Shutting Down\n");
	cErrorLogger::Log().WriteToConsole("#######################################################\n");
	cErrorLogger::Log().DestroyConsole();

	pEngine->cleanup();

	if (!UnregisterClass(CLASSNAME, hInst))               // Are We Able To Unregister Class
	{
		MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInst = NULL;                         // Set hInstance To NULL
	}
}

