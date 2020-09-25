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
}

void TestState::Init()
{
	World* w = Engine::getWorld();
	w->LoadMap("Test Map", "", true);
	w->LoadMap("Test2 Map", "");


	p = new PlayerEnt();
	p->Load();

	Engine::SetCam(p->getCam()->getCam2D());
}

void TestState::UpdateOrth(const float& dt)
{ 

	p->Update(dt);


	//model = glm::translate(glm::inverse(Engine::get().default_cam->ViewMatrix), glm::vec3((float)Engine::get().WindowWidth/2.0f, (float)Engine::get().WindowHeight/2.0f, 0.0f));
}

void TestState::Render()
{


}

void TestState::RenderOrth()
{
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
			p->dx = -10;
			p->SetState(states::WALK_LEFT);
		}break;
		case ENGINE_KEY_D:
		{
			p->dx = 10;
			p->SetState(states::WALK_RIGHT);
		}break;
		case ENGINE_KEY_W:
		{
			p->dy = -10;
			p->SetState(states::WALK_UP);
		}break;
		case ENGINE_KEY_S:
		{
			p->dy = 10;
			p->SetState(states::WALK_DOWN);
		}break;
		case ENGINE_KEY_1:
		{
			p->SetState(states::SPELL);
		}break;
		case ENGINE_KEY_2:
		{
			World* w = Engine::getWorld();
			w->SetMap("Test2 Map");
		} break;
		case ENGINE_KEY_3:
		{
			World* w = Engine::getWorld();
			w->SetMap("Test Map");
		} break;
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
				p->dx = 0;
				if (p->dx == 0 && p->dy == 0)
				{
					p->SetState(states::IDLE);
				}
			}
		}break;
		case ENGINE_KEY_D:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_A))
			{
				p->dx = 0;
				if (p->dx == 0 && p->dy == 0)
				{
					p->SetState(states::IDLE);
				}
			}
		}break;
		case ENGINE_KEY_W:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_S))
			{
				p->dy = 0;
				if (p->dx == 0 && p->dy == 0)
				{
					p->SetState(states::IDLE);
				}
			}
		}break;
		case ENGINE_KEY_S:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_W))
			{
				p->dy = 0;
				if (p->dx == 0 && p->dy == 0)
				{
					p->SetState(states::IDLE);
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