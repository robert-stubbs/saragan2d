#include "GamePCH.h"
#include "OpenGLShader.h"
#include "Shader.h"

#include "Engine.h"
#include "Line.h"
#include "Triangle.h"
#include "Square.h"


using namespace GameEngine;

Triangle p;
Line t;
//Square sq;

// Time Step Videos
// https://stackoverflow.com/questions/20390028/c-using-glfwgettime-for-a-fixed-time-step
// https://www.youtube.com/watch?v=rh31YOZh5ZM&t
static double limitFPS = 1.0 / 60.0;

void PreLoad()
{
    Engine& e = Engine::get();

    e.SetAssetDir("C:/Assets/");
    e.SetWindowName("Saragan");
    e.SetWindowSize(800, 600);
    e.PreInit();        

}

void Load()
{
    Engine::get().Init();

    // After Engine Initialisation should be done here

}

void PostLoad()
{
    Engine::get().PostInit();

    p = Triangle();
    p.Init();

    t = Line();
    t.Init(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f, glm::vec4(1.0f, 1.0f,1.0f, 1.0f));

    // After Engine Post Initialisation should be done here
    Engine::getRenderer().CheckError();
}

void Update(float dt)
{
    // put this in its own function in case you want to do 
    // your own updates outside of the engine
    Engine::get().Update(dt);

    p.Update(dt);
    t.Update(dt);

    Engine::getRenderer().CheckError();
}

void Render()
{
    Engine::get().Render();
    // put this in its own function in case you want to do 
    // your own renders outside of the engine

    Engine::getShader().BindNewShader("DEFAULT2D");

    Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], glm::mat4(1.0f), 1, false);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], glm::mat4(1.0f), 1, false);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

    //Render Here
    p.Render();
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
    PreLoad();
    Load();
    PostLoad();

    double lastTime = glfwGetTime(), timer = lastTime;
    double deltaTime = 0, nowTime = 0;
    int frames = 0, updates = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(Engine::get().window))
    {
        // - Measure time
        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime) / limitFPS;
        lastTime = nowTime;

        // - Only update at 60 frames / s
        while (deltaTime >= 1.0) {
            Update((float)deltaTime);
            updates++;
            deltaTime--;
        }

        Render();
        frames++;

        // - Reset after one second
        if (glfwGetTime() - timer > 1.0) {
            timer++;
            std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
            updates = 0, frames = 0;
        }

    }

    CleanUp();
    return 0;
}