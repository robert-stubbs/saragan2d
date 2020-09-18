#include "GamePCH.h"
#include "TestState.h"
#include "Engine.h"
#include "Camera2D.h"
#include "Shader.h"
#include "Texture.h"
#include "BatchRenderer.h"
#include "Map.h"
#include "SafeDelete.h"

using namespace GameEngine;

TestState::TestState() : State()
{

}

TestState::~TestState()
{
	m->Cleanup();
	SAFE_DELETE(m);
}

void TestState::Init()
{
	m = new Map();
	m->Init("Test Map", "");
	m->ThreadLoad();    

	p = new PlayerEnt();
	p->Load();
}

void TestState::UpdateOrth(const float& dt)
{ 
	m->Update(dt);


	model = glm::translate(glm::inverse(Engine::get().default_cam->ViewMatrix), glm::vec3((float)Engine::get().WindowWidth/2.0f, (float)Engine::get().WindowHeight/2.0f, 0.0f));
}

void TestState::RenderOrth()
{
	//Engine::getRenderer().EnableDepthTest(false);
	//Engine::getRenderer().EnableBlend(true, GameEngine::BLEND_TYPE::SRC_ALPHA, GameEngine::BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

	//m->Render();

	//Engine::getRenderer().EnableBlend(false);
	//Engine::getRenderer().EnableDepthTest(true);
}

void TestState::DoENTER()
{ 

}

void TestState::DoEXIT()
{ 

}

void TestState::KeyDown(int Key)
{ 
	switch (Input::Get().GetKey(Key))
	{
		case ENGINE_KEY_A:
		{
			Engine::get().default_cam->dx = -10;
			//spriteTest.SetAnim("WalkLeft");
		}break;
		case ENGINE_KEY_D:
		{
			//std::cout << "Setting Anim Walk Right" << std::endl;
			Engine::get().default_cam->dx = 10;
			//spriteTest.SetAnim("WalkRight");
		}break;
		case ENGINE_KEY_W:
		{
			Engine::get().default_cam->dy = -10;
			//spriteTest.SetAnim("WalkUp");
		}break;
		case ENGINE_KEY_S:
		{
			Engine::get().default_cam->dy = 10;
			//spriteTest.SetAnim("Walk");
		}break;
		case ENGINE_KEY_1:
		{
			//spriteTest.SetAnim("Spell");
		}break;
	}
}

void TestState::KeyUp(int Key)
{
	switch (Input::Get().GetKey(Key))
	{
		case ENGINE_KEY_A:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_D))
			{
				Engine::get().default_cam->dx = 0;
				if (Engine::get().default_cam->dx == 0 && Engine::get().default_cam->dy == 0)
				{
					//spriteTest.SetAnim("Idle");
				}
			}
		}break;
		case ENGINE_KEY_D:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_A))
			{
				Engine::get().default_cam->dx = 0;
				if (Engine::get().default_cam->dx == 0 && Engine::get().default_cam->dy == 0)
				{
					//spriteTest.SetAnim("Idle");
				}
			}
		}break;
		case ENGINE_KEY_W:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_S))
			{
				Engine::get().default_cam->dy = 0;
				if (Engine::get().default_cam->dx == 0 && Engine::get().default_cam->dy == 0)
				{
					//spriteTest.SetAnim("Idle");
				}
			}
		}break;
		case ENGINE_KEY_S:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_W))
			{
				Engine::get().default_cam->dy = 0;
				if (Engine::get().default_cam->dx == 0 && Engine::get().default_cam->dy == 0)
				{
					//spriteTest.SetAnim("Idle");
				}
			}
		}break;
	}
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