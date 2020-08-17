#include "EnginePCH.h"
#include "Engine.h"

#include "OpenGLRenderer.h"
#include "StateMachine.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "SafeDelete.h"

#include "Camera.h"
#include "Camera2D.h"
#include "Font.h"


Engine* Engine::engine = nullptr;

Engine::Engine()
{
	engine = this;

	renderer = new OpenGLRenderer();
	System = new SystemManager();
	EntityMgr = new EntityManager();

}

Engine::~Engine()
{
	SAFE_DELETE(EntityMgr);

	System->CleanUp();
	SAFE_DELETE(System);
}

bool Engine::init(HWND hWnd, int Width, int Height)
{
	width = (float)Width;
	height = (float)Height;

	renderer->init(hWnd);

	System->Init();

	std::string asset_dir = "C:/Assets/";
	std::string ft = asset_dir + "Font/Vera.ttf";
	font = new Font(30, ft.c_str());

	GameFSM = new StateMachine();


	pCam = new Camera(Engine::getEngine().width, Engine::getEngine().height);
	pCam2D = new Camera2D(Engine::getEngine().width, Engine::getEngine().height);

	return true;
}

bool Engine::PostInit()
{
	return renderer->PostInit();
}

bool Engine::load()
{
	return renderer->load();
}

bool Engine::Update(float DeltaTime)
{
	pCam->Update(DeltaTime);

	System->Update(DeltaTime);

	GameFSM->Update(DeltaTime);

	renderer->Update(DeltaTime);

	return true;
}

bool Engine::UpdateOrth(float DeltaTime)
{
	pCam2D->Update(DeltaTime);

	GameFSM->UpdateOrth(0);

	renderer->UpdateOrtho(DeltaTime);
	return true;
}

void Engine::render()
{
	renderer->render(GameFSM, System, pCam->ProjectionMatrix, pCam->ViewMatrix);
}

void Engine::renderOrth()
{
	renderer->renderOrtho(GameFSM, System, pCam2D->ProjectionMatrix, pCam2D->ViewMatrix);
}

bool Engine::cleanup()
{
	return renderer->cleanup();
}

bool Engine::ResizeWindow(int Width, int Height)
{
	width = (float)Width;
	height = (float)Height;
	return renderer->ResizeWindow(Width, Height);
}

void Engine::KeyDown(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	GameFSM->KeyDown(Msg, wParam, lParam);
}

void Engine::KeyUp(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	GameFSM->KeyUp(Msg, wParam, lParam);
}


void Engine::MouseDown(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	GameFSM->MouseDown(Msg, wParam, lParam);
}

void Engine::MouseUp(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	GameFSM->MouseUp(Msg, wParam, lParam);
}

void Engine::MouseMove(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	GameFSM->MouseMove(Msg, wParam, lParam);
}
