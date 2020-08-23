#include "GamePCH.h"
#include "OpenGLShader.h"
#include "Shader.h"

#include "Engine.h"
#include "Line.h"
#include "Triangle.h"
#include "Square.h"
#include "Camera2D.h"
#include "Context.h"
#include "ContextPlatform.h"

#include "Input.h"

using namespace GameEngine;

Triangle t;

// Time Step Videos
// https://stackoverflow.com/questions/20390028/c-using-glfwgettime-for-a-fixed-time-step
// https://www.youtube.com/watch?v=rh31YOZh5ZM&t
static double limitFPS = 1.0 / 60.0;

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

void Load()
{
    Engine::get().Init();

    // After Engine Initialisation should be done here

}

void PostLoad()
{
    Engine::get().PostInit();

    // After Engine Post Initialisation should be done here
    t.Init(0.0f,0.0f, 100.0f, 100.0f, 100.0f, 0.0f);

}

void Update(float dt)
{

    // put this in its own function in case you want to do 
    // your own updates outside of the engine
    Engine::get().Update(dt);

    t.Update(dt);


}

void Render()
{
    Engine::get().Render();
    // put this in its own function in case you want to do 
    // your own renders outside of the engine

    Engine::getShader().BindNewShader("DEFAULT2D");

    Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], Engine::get().cam->ProjectionMatrix, 1, false);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], Engine::get().cam->ViewMatrix, 1, false);
    //Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], glm::mat4(1.0f), 1, false);
    //Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], glm::mat4(1.0f), 1, false);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

    t.Render();

    Engine::get().RenderEnd();
}

void CleanUp()
{
    //Clean up anything you have created prior to this line
    Engine::get().Cleanup();
}

int main(void)
{
    if (!PreLoad())
    {
        return false;
    }

    Load();
    PostLoad();

    //double lastTime = glfwGetTime(), timer = lastTime;
    //double deltaTime = 0, nowTime = 0;
    //int frames = 0, updates = 0;

    ContextPlatform& platform = Engine::getContext().GetWindow();

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

    ///* Loop until the user closes the window */
    //while (!glfwWindowShouldClose(((GLFWwindow*)platform.GetWindowHandle())))
    //{
    //    // - Measure time
    //    nowTime = glfwGetTime();
    //    deltaTime += (nowTime - lastTime) / limitFPS;
    //    lastTime = nowTime;

    //    // - Only update at 60 frames / s
    //    while (deltaTime >= 1.0) {
    //        Update((float)deltaTime);
    //        updates++;
    //        deltaTime--;
    //    }

    //    Render();


    //    frames++;

    //    // - Reset after one second
    //    if (glfwGetTime() - timer > 1.0) {
    //        timer++;
    //        std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
    //        updates = 0, frames = 0;
    //    }

    //}

    CleanUp();
    return 0;
}