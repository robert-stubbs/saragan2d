#include "GamePCH.h"

#include "Engine.h"
#include "Types.h"

#include "TestState.h"
#include "RayState.h"

using namespace GameEngine;

bool PreLoad()
{
    Engine& e = Engine::get();

    e.SetPlatform(PLATFORM::WINDOWS);
    e.SetRenderEngine(RenderEngines::OpenGL);
    e.SetAssetDir("C:/Assets/");
    e.SetWindowName("Saragan");
    e.SetWindowSize(800, 600);
    if (!e.PreInit()) {
        return false;
    }
    return true;
}

void PostLoad()
{     
    Engine::state().AddState(new TestState(), false);
    Engine::state().AddState(new RayState(), true);
}

int main(void)
{
    if (!PreLoad())
    {
        return false;
    }

    Engine::get().Init();
    Engine::get().PostInit();
    PostLoad();
    Engine::getContext().GetWindow().RenderLoop();
    Engine::get().Cleanup();

    return 0;
}