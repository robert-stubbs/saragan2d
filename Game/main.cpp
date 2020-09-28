#include "GamePCH.h"

#include "Engine.h"
#include "Types.h"

#include "cIni.h"

#include "TestState.h"
#include "RayState.h"
#include "MinesweeperState.h"

using namespace GameEngine;

bool PreLoad()
{
    Engine& e = Engine::get();

    LOG("Loading Ini File");

    cIni* ini = new cIni("C:/Assets/Engine.ini");
    

    LOG("Setting Platform: " + ini->GetstringOption("Startup", "Platform", "WINDOWS"));
    e.SetPlatform(ini->GetstringOption("Startup", "Platform", "WINDOWS"));

    LOG("Setting Renderer:" + ini->GetstringOption("Startup", "Renderer", "OpenGL"));
    e.SetRenderEngine(ini->GetstringOption("Startup", "Renderer", "OpenGL"));

    LOG("Setting Asset Directory: " + ini->GetstringOption("Startup", "AssetDir", "C:/Assets/"));
    e.SetAssetDir(ini->GetstringOption("Startup", "AssetDir", "C:/Assets/"));

    e.SetWindowName(ini->GetstringOption("Window", "WindowName", "Default"));
    e.SetWindowSize(ini->GetIntOption("Window","WindowSizeX", 800), ini->GetIntOption("Window", "WindowSizeY", 600));

    LOG("Pre-Initializing Engine");
    if (!e.PreInit()) {
        return false;
    }
    return true;
}

void PostLoad()
{     
    //Engine::state().AddState(new RayState(), false);
    //Engine::state().AddState(new MinesweeperState(), false);
    Engine::state().AddState(new TestState(), true);
}

int main(void)
{
    if (!PreLoad())
    {
        return false;
    }

    LOG("Initializing Engine");
    Engine::get().Init();
    Engine::get().PostInit();

    LOG("Post Load");
    PostLoad();

    LOG("Starting Render Loop");
    Engine::getContext().Get().RenderLoop();
    Engine::get().Cleanup();

    return 0;
}