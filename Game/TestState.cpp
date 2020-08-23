#include "GamePCH.h"
#include "TestState.h"
#include "Engine.h"
#include "Camera2D.h"
#include "Shader.h"

using namespace GameEngine;

TestState::TestState() : State()
{

}

TestState::~TestState()
{

}

void TestState::Init()
{
	std::cout << "we got here" << std::endl;

	t.Init(0.0f, 0.0f, 100.0f, 100.0f, 100.0f, 0.0f);
}

void TestState::UpdateOrth(const float& dt)
{ 
	t.Update(dt);
}

void TestState::RenderOrth()
{ 
    Engine::getShader().BindNewShader("DEFAULT2D");

    Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], Engine::get().cam->ProjectionMatrix, 1, false);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], Engine::get().cam->ViewMatrix, 1, false);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

    t.Render();
}

void TestState::DoENTER()
{ 

}

void TestState::DoEXIT()
{ 

}

void TestState::KeyDown(int Key)
{ 

}

void TestState::KeyUp(int Key)
{ 

}

void TestState::MouseDown(int button)
{ 

}

void TestState::MouseUp(int button)
{ 

}

void TestState::MouseMove(float x, float y)
{ 

}