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

	// width 832 
	// 13 / 832
	// 0.0769
	// Height 1344
	// 21 / 1344
	// 0.0476
	float startY = 0.0476 * 10;
	float EndY = 0.0476 * 11;

	// walk is  0.0476 * 11 (down)
	// 9 sprites 0.1428

	GameEngine::SpriteAnimDef idle = SpriteAnimDef();
	idle.frames = std::vector<SpriteAnimFrame>();
	idle.frames.push_back({ {0.0f   ,startY}, {0.0769f,EndY}, 200, 200 });
	idle.frame_speed = 0.1f;
	idle.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef walk = SpriteAnimDef();
	walk.frames = std::vector<SpriteAnimFrame>();
	walk.frames.push_back({ {0.0f   ,startY}, {0.0769f,EndY}, 200, 200 });
	walk.frames.push_back({ {0.0769f,startY}, {0.1538f,EndY}, 200, 200 });
	walk.frames.push_back({ {0.1538f,startY}, {0.2307f,EndY}, 200, 200 });
	walk.frames.push_back({ {0.2307f,startY}, {0.3076f,EndY}, 200, 200 });
	walk.frames.push_back({ {0.3076f,startY}, {0.3845f,EndY}, 200, 200 });
	walk.frames.push_back({ {0.3845f,startY}, {0.4614f,EndY}, 200, 200 });
	walk.frames.push_back({ {0.4614f,startY}, {0.5383f,EndY}, 200, 200 });
	walk.frames.push_back({ {0.5383f,startY}, {0.6152f,EndY}, 200, 200 });
	walk.frames.push_back({ {0.6152f,startY}, {0.6921f,EndY}, 200, 200 });
	walk.frame_speed = 0.1f;
	walk.texture_id = t.TextureID;

	GameEngine::SpriteAnimDef spell = SpriteAnimDef();
	spell.frames = std::vector<SpriteAnimFrame>();
	spell.frames.push_back({ {0.0f,   0.0952f}, {0.0769f,0.1428f}, 200, 200 });
	spell.frames.push_back({ {0.0769f,0.0952f}, {0.1538f,0.1428f}, 200, 200 });
	spell.frames.push_back({ {0.1538f,0.0952f}, {0.2307f,0.1428f}, 200, 200 });
	spell.frames.push_back({ {0.2307f,0.0952f}, {0.3076f,0.1428f}, 200, 200 });
	spell.frames.push_back({ {0.3076f,0.0952f}, {0.3845f,0.1428f}, 200, 200 });
	spell.frames.push_back({ {0.3845f,0.0952f}, {0.4614f,0.1428f}, 200, 200 });
	spell.frames.push_back({ {0.4614f,0.0952f}, {0.5383f,0.1428f}, 200, 200 });
	spell.frame_speed = 0.1f;
	spell.texture_id = t.TextureID;

	GameEngine::AnimSprite sp = AnimSprite();
	sp.name = "TestSprite";
	sp.anims = std::map<std::string, SpriteAnimDef>();
	sp.verts = std::vector<vert2D>();
	sp.vert_indices = std::vector<int>();
	sp.anims["Idle"] = idle;
	sp.anims["Walk"] = walk;
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
		}break;
		case ENGINE_KEY_D:
		{
			Engine::get().cam->dx = -10;
		}break;
		case ENGINE_KEY_W:
		{
			Engine::get().cam->dy = 10;
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
			}
		}break;
		case ENGINE_KEY_D:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_A))
			{
				Engine::get().cam->dx = 0;
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