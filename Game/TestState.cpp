#include "GamePCH.h"
#include "TestState.h"
#include "Engine.h"
#include "Camera2D.h"
#include "Shader.h"
#include "Texture.h"

using namespace GameEngine;

TestState::TestState() : State()
{

}

TestState::~TestState()
{

}

void TestState::Init()
{

	t = Texture();
	if (t.LoadFile(Engine::get().asset_dir + "Textures/testsprite.png", TEXTURETYPES::SARAGAN_PNG))
	{
		t.GenerateAlphaBuffer();
	}

	GameEngine::SpriteAnimDef idle = SpriteAnimDef();
	idle.frames = std::vector<SpriteAnimFrame>();
	idle.frame_speed = 0.1f;
	idle.sheet_row = 10;
	idle.sheet_column = 0;
	idle.number_of_frames = 1;
	idle.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef walk = SpriteAnimDef();
	walk.frames = std::vector<SpriteAnimFrame>();
	walk.sheet_row = 10;
	walk.sheet_column = 0;
	walk.number_of_frames = 9;
	walk.frame_speed = 0.1f;
	walk.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef walkleft = SpriteAnimDef();
	walkleft.frames = std::vector<SpriteAnimFrame>();
	walkleft.sheet_row = 9;
	walkleft.sheet_column = 0;
	walkleft.number_of_frames = 9;
	walkleft.frame_speed = 0.1f;
	walkleft.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef walkright = SpriteAnimDef();
	walkright.frames = std::vector<SpriteAnimFrame>();
	walkright.sheet_row = 11;
	walkright.sheet_column = 0;
	walkright.number_of_frames = 9;
	walkright.frame_speed = 0.1f;
	walkright.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef walkup = SpriteAnimDef();
	walkup.frames = std::vector<SpriteAnimFrame>();
	walkup.sheet_row = 8;
	walkup.sheet_column = 0;
	walkup.number_of_frames = 9;
	walkup.frame_speed = 0.1f;
	walkup.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef spell = SpriteAnimDef();
	spell.frames = std::vector<SpriteAnimFrame>();
	spell.frame_speed = 0.1f;
	spell.reset_on_start = true;
	spell.sheet_row = 2;
	spell.sheet_column = 0;
	spell.number_of_frames = 7;
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
	sp.anims["Idle"] = idle;
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
}

void TestState::RenderOrth()
{ 
    Engine::getShader().BindNewShader("DEFAULT2D");

    Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], Engine::get().cam->ProjectionMatrix, 1, false);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], Engine::get().cam->ViewMatrix, 1, false);
    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

	spriteTest.Render();
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
			Engine::get().cam->dx = 10;
			spriteTest.SetAnim("WalkLeft");
		}break;
		case ENGINE_KEY_D:
		{
			Engine::get().cam->dx = -10;
			spriteTest.SetAnim("WalkRight");
		}break;
		case ENGINE_KEY_W:
		{
			Engine::get().cam->dy = 10;
			spriteTest.SetAnim("WalkUp");
		}break;
		case ENGINE_KEY_S:
		{
			Engine::get().cam->dy = -10;
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
				spriteTest.SetAnim("Idle");
			}
		}break;
		case ENGINE_KEY_D:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_A))
			{
				Engine::get().cam->dx = 0;
				spriteTest.SetAnim("Idle");
			}
		}break;
		case ENGINE_KEY_W:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_S))
			{
				Engine::get().cam->dy = 0;
				spriteTest.SetAnim("Idle");
			}
		}break;
		case ENGINE_KEY_S:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_W))
			{
				Engine::get().cam->dy = 0;
				spriteTest.SetAnim("Idle");
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