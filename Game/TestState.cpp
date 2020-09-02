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
	
	t = Texture();
	if (t.LoadFile(Engine::get().asset_dir + "Textures/testsprite.png", TEXTURETYPES::SARAGAN_PNG))
	{
		t.GenerateAlphaBuffer();
	}

	GameEngine::SpriteAnimDef idle = SpriteAnimDef();
	idle.frames = std::vector<SpriteAnimFrame>();
	idle.frame_width = 100;
	idle.frame_height = 100;
	idle.frame_speed = 0.1f;
	idle.sheet_row = 10;
	idle.sheet_column = 0;
	idle.number_of_frames = 1;
	idle.loop_count = 0;
	idle.wait_til_finished = false;
	idle.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef walk = SpriteAnimDef();
	walk.frame_width = 100;
	walk.frame_height = 100;
	walk.sheet_row = 10;
	walk.sheet_column = 0;
	walk.number_of_frames = 9;
	walk.frame_speed = 0.1f;
	walk.loop_count = 0;
	walk.wait_til_finished = false;
	walk.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef walkleft = SpriteAnimDef();
	walkleft.frame_width = 100;
	walkleft.frame_height = 100;
	walkleft.sheet_row = 9;
	walkleft.sheet_column = 0;
	walkleft.number_of_frames = 9;
	walkleft.frame_speed = 0.1f;
	walkleft.loop_count = 0;
	walkleft.wait_til_finished = false;
	walkleft.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef walkright = SpriteAnimDef();
	walkright.frame_width = 100;
	walkright.frame_height = 100;
	walkright.sheet_row = 11;
	walkright.sheet_column = 0;
	walkright.number_of_frames = 9;
	walkright.frame_speed = 0.1f;
	walkright.loop_count = 0;
	walkright.wait_til_finished = false;
	walkright.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef walkup = SpriteAnimDef();
	walkup.frame_width = 100;
	walkup.frame_height = 100;
	walkup.sheet_row = 8;
	walkup.sheet_column = 0;
	walkup.number_of_frames = 9;
	walkup.frame_speed = 0.1f;
	walkup.loop_count = 0;
	walkup.wait_til_finished = false;
	walkup.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef spell = SpriteAnimDef();
	spell.frame_width = 100;
	spell.frame_height = 100;
	spell.frame_speed = 0.1f;
	spell.sheet_row = 2;
	spell.sheet_column = 0;
	spell.number_of_frames = 7;
	spell.loop_count = 1;
	spell.reset_on_start = true;
	spell.wait_til_finished = true;
	spell.texture_id = t.TextureID;

	GameEngine::AnimSprite sp = AnimSprite();
	sp.name = "TestSprite";
	sp.anims = std::map<std::string, SpriteAnimDef>();
	sp.verts = std::vector<vert2D>();
	sp.vert_indices = std::vector<int>();
	sp.sheet_width = 832;
	sp.sheet_height = 1344;
	sp.sheet_columns = 13;
	sp.sheet_rows = 21;
	sp.idle_anim = "Idle";
	sp.anims[sp.idle_anim] = idle;
	sp.anims["Walk"] = walk;
	sp.anims["WalkLeft"] = walkleft;
	sp.anims["WalkRight"] = walkright;
	sp.anims["WalkUp"] = walkup;
	sp.anims["Spell"] = spell;

	spriteTest = Sprite();
	spriteTest.m_shader = "DEFAULT2D";
	spriteTest.LoadAnimSprite(sp);
	spriteTest.SetAnim("Idle");

}

void TestState::UpdateOrth(const float& dt)
{ 
	spriteTest.Update(dt);
	m->Update(dt);


	model = glm::translate(glm::inverse(Engine::get().cam->ViewMatrix), glm::vec3((float)Engine::get().WindowWidth/2.0f, (float)Engine::get().WindowHeight/2.0f, 0.0f));
}

void TestState::RenderOrth()
{
	Engine::getRenderer().EnableDepthTest(false);
	Engine::getRenderer().EnableBlend(true, GameEngine::BLEND_TYPE::SRC_ALPHA, GameEngine::BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

	m->Render();

	if (Engine::getRenderer().CurrentTextureID != t.TextureID)
	{
		Engine::getRenderer().CurrentTextureID = t.TextureID;

		Engine::getRenderer().BindTextureBuffer(t.TextureID);
	}

	Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], model, 1, false);

	spriteTest.Render();

	Engine::getRenderer().EnableBlend(false);
	Engine::getRenderer().EnableDepthTest(true);
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
			Engine::get().cam->dx = -10;
			spriteTest.SetAnim("WalkLeft");
		}break;
		case ENGINE_KEY_D:
		{
			//std::cout << "Setting Anim Walk Right" << std::endl;
			Engine::get().cam->dx = 10;
			spriteTest.SetAnim("WalkRight");
		}break;
		case ENGINE_KEY_W:
		{
			Engine::get().cam->dy = -10;
			spriteTest.SetAnim("WalkUp");
		}break;
		case ENGINE_KEY_S:
		{
			Engine::get().cam->dy = 10;
			spriteTest.SetAnim("Walk");
		}break;
		case ENGINE_KEY_1:
		{
			spriteTest.SetAnim("Spell");
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
				Engine::get().cam->dx = 0;
				if (Engine::get().cam->dx == 0 && Engine::get().cam->dy == 0)
				{
					spriteTest.SetAnim("Idle");
				}
			}
		}break;
		case ENGINE_KEY_D:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_A))
			{
				Engine::get().cam->dx = 0;
				if (Engine::get().cam->dx == 0 && Engine::get().cam->dy == 0)
				{
					spriteTest.SetAnim("Idle");
				}
			}
		}break;
		case ENGINE_KEY_W:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_S))
			{
				Engine::get().cam->dy = 0;
				if (Engine::get().cam->dx == 0 && Engine::get().cam->dy == 0)
				{
					spriteTest.SetAnim("Idle");
				}
			}
		}break;
		case ENGINE_KEY_S:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_W))
			{
				Engine::get().cam->dy = 0;
				if (Engine::get().cam->dx == 0 && Engine::get().cam->dy == 0)
				{
					spriteTest.SetAnim("Idle");
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