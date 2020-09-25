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

	Engine::SetCam(p->getCam()->getCam2D());
}

void TestState::UpdateOrth(const float& dt)
{ 
	m->Update(dt);
	p->Update(dt);


	//model = glm::translate(glm::inverse(Engine::get().default_cam->ViewMatrix), glm::vec3((float)Engine::get().WindowWidth/2.0f, (float)Engine::get().WindowHeight/2.0f, 0.0f));
}

void TestState::Render()
{
	Engine::getRenderer().EnableDepthTest(false);
	Engine::getRenderer().EnableBlend(true, GameEngine::BLEND_TYPE::SRC_ALPHA, GameEngine::BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

	m->Render();

	Engine::getRenderer().EnableBlend(false);
	Engine::getRenderer().EnableDepthTest(true);
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