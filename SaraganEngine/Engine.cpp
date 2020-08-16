#include "EnginePCH.h"
#include "Engine.h"

#include "OpenGLRenderer.h"
#include "StateMachine.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "SafeDelete.h"

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

bool Engine::init(HWND hWnd)
{
	renderer->init(hWnd);

	System->Init();

	GameFSM = new StateMachine();


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
	renderer->Update(DeltaTime);

	System->Update(DeltaTime);

	GameFSM->Update(DeltaTime);

	return true;
}

bool Engine::UpdateOrth(float DeltaTime)
{
	renderer->UpdateOrtho(DeltaTime);

	GameFSM->UpdateOrth(0);
	return true;
}

void Engine::render()
{
	return renderer->render(GameFSM, System, ProjectionMatrix, viewMatrix);
}

void Engine::renderOrth()
{
	return renderer->renderOrtho(GameFSM, System, ProjectionMatrix, viewMatrix);
}

bool Engine::cleanup()
{
	return renderer->cleanup();
}

bool Engine::ResizeWindow(int Width, int Height)
{
	return renderer->ResizeWindow(Width, Height);
	width = (float)Width;
	height = (float)Height;
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
