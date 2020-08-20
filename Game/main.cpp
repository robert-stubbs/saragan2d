#include "GamePCH.h"
#include "OpenGLShader.h"
#include "Shader.h"

#include "Engine.h"

using namespace GameEngine;

// Time Step Videos
// https://stackoverflow.com/questions/20390028/c-using-glfwgettime-for-a-fixed-time-step
// https://www.youtube.com/watch?v=rh31YOZh5ZM&t
static double limitFPS = 1.0 / 60.0;

std::vector<vert2D> verts = std::vector<vert2D>();
unsigned int        VBO;
unsigned int        VAIO;

void PreLoad();
void Load();
void PostLoad();
void Update(float dt);
void Render();
void CleanUp();

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

void PreLoad()
{
    Engine& e = Engine::get();

    e.SetAssetDir("C:/Assets/");
    e.SetWindowName("Saragan");
    e.SetWindowSize(800, 600);
    e.PreInit();  
    
    // After Engine Pre Initialisation should be done here


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
    
    Engine::getShader().bindings.push_back({ SHADER_TYPES::ATRIBLOCATION, "in_Position", 0 });
    Engine::getShader().bindings.push_back({ SHADER_TYPES::ATRIBLOCATION, "in_Texture", 1 });
    Engine::getShader().bindings.push_back({ SHADER_TYPES::ATRIBLOCATION, "in_Color", 2 });

    Engine::getShader().bindings.push_back({ SHADER_TYPES::UNIFORM, "projectionMatrix", 0 });
    Engine::getShader().bindings.push_back({ SHADER_TYPES::UNIFORM, "viewMatrix", 0 });
    Engine::getShader().bindings.push_back({ SHADER_TYPES::UNIFORM, "modelMatrix", 0 });
    Engine::getShader().bindings.push_back({ SHADER_TYPES::UNIFORM, "is_Text", 0 });

    Engine::getShader().init(Engine::get().asset_dir + "Shaders/VertexShader.glsl", Engine::get().asset_dir + "Shaders/FragmentShader.glsl");

    Engine::getShader().bind();

    verts.push_back({ {-0.5f, -0.5f, 0.0f, 1.0f }, {-99.0f,-99.0f},  {1.0f, 0.0f, 0.0f, 1.0f } });
    verts.push_back({ { 0.0f,  0.5f, 0.0f, 1.0f }, {-99.0f,-99.0f},  {0.0f, 1.0f, 0.0f, 1.0f } });
    verts.push_back({ { 0.5f, -0.5f, 0.0f, 1.0f }, {-99.0f,-99.0f},  {0.0f, 0.0f, 1.0f, 1.0f } });

    Engine::getRenderer().GenerateBuffer(VBO, verts);
    Engine::getRenderer().VertexStructurePointerF(Engine::getShader()["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
    Engine::getRenderer().VertexStructurePointerF(Engine::getShader()["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
    Engine::getRenderer().VertexStructurePointerF(Engine::getShader()["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

    Engine::getRenderer().UnbindVertexBuffer();
}

void Update(float dt)
{
    // put this in its own function in case you want to do 
    // your own updates outside of the engine
    Engine::get().Update(dt);
}

void Render()
{
    Engine::get().Render();
    // put this in its own function in case you want to do 
    // your own renders outside of the engine

    Engine::getRenderer().UniformInt(Engine::getShader()["is_Text"], 0);
    Engine::getRenderer().UniformMat4(Engine::getShader()["projectionMatrix"], glm::mat4(1.0f), 1, false);
    Engine::getRenderer().UniformMat4(Engine::getShader()["viewMatrix"], glm::mat4(1.0f), 1, false);
    Engine::getRenderer().UniformMat4(Engine::getShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

    Engine::getRenderer().EnableBlend(true, BLEND_TYPE::SRC_ALPHA, BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

    Engine::getRenderer().BindVertexBuffer(VBO);


    Engine::getRenderer().DrawArrays(DRAW_TYPE::TRIANGLES, (GLsizei)verts.size());

    Engine::getRenderer().UnbindVertexBuffer();

    Engine::getRenderer().EnableBlend(false);

    Engine::get().RenderEnd();
}

void CleanUp()
{
    //Clean up anything you have created prior to this line
    Engine::get().Cleanup();
}

