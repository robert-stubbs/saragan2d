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
	// 9 sprites
	GameEngine::SpriteAnimFrame walk_one   = { {0.0f   ,startY}, {0.0769f,EndY}, 200, 200 };
	GameEngine::SpriteAnimFrame walk_two   = { {0.0769f,startY}, {0.1538f,EndY}, 200, 200 };
	GameEngine::SpriteAnimFrame walk_three = { {0.1538f,startY}, {0.2307f,EndY}, 200, 200 };
	GameEngine::SpriteAnimFrame walk_four  = { {0.2307f,startY}, {0.3076f,EndY}, 200, 200 };
	GameEngine::SpriteAnimFrame walk_five  = { {0.3076f,startY}, {0.3845f,EndY}, 200, 200 };
	GameEngine::SpriteAnimFrame walk_six   = { {0.3845f,startY}, {0.4614f,EndY}, 200, 200 };
	GameEngine::SpriteAnimFrame walk_seven = { {0.4614f,startY}, {0.5383f,EndY}, 200, 200 };
	GameEngine::SpriteAnimFrame walk_eight = { {0.5383f,startY}, {0.6152f,EndY}, 200, 200 };
	GameEngine::SpriteAnimFrame walk_nine  = { {0.6152f,startY}, {0.6921f,EndY}, 200, 200 };

	GameEngine::SpriteAnimDef walk = SpriteAnimDef();
	walk.frames = std::vector<SpriteAnimFrame>();
	walk.frames.push_back(walk_one);
	walk.frames.push_back(walk_two);
	walk.frames.push_back(walk_three);
	walk.frames.push_back(walk_four);
	walk.frames.push_back(walk_five);
	walk.frames.push_back(walk_six);
	walk.frames.push_back(walk_seven);
	walk.frames.push_back(walk_eight);
	walk.frames.push_back(walk_nine);
	walk.frame_speed = 0.1f;
	walk.texture_id = t.TextureID;


	GameEngine::SpriteAnimFrame one = { {0.0f,0.1f}, { 0.0769f,0.15f}, 200, 200 };
	GameEngine::SpriteAnimFrame two = { {0.0769f,0.1f}, {0.1538f,0.15f}, 200, 200 };
	GameEngine::SpriteAnimFrame three = { {0.1538f,0.1f}, {0.2307f,0.15f}, 200, 200 };
	GameEngine::SpriteAnimFrame four = { {0.2307f,0.1f}, {0.3076f,0.15f}, 200, 200 };
	GameEngine::SpriteAnimFrame five = { {0.3076f,0.1f}, {0.3845f,0.15f}, 200, 200 };
	GameEngine::SpriteAnimFrame six = { {0.3845f,0.1f}, {0.4614f,0.15f}, 200, 200 };
	GameEngine::SpriteAnimFrame seven = { {0.4614f,0.1f}, {0.5383f,0.15f}, 200, 200 };

	GameEngine::SpriteAnimDef spell = SpriteAnimDef();
	spell.frames = std::vector<SpriteAnimFrame>();
	spell.frames.push_back(one);
	spell.frames.push_back(two);
	spell.frames.push_back(three);
	spell.frames.push_back(four);
	spell.frames.push_back(five);
	spell.frames.push_back(six);
	spell.frames.push_back(seven);
	spell.frame_speed = 0.1f;
	spell.texture_id = t.TextureID;

	GameEngine::AnimSprite sp = AnimSprite();
	sp.name = "TestSprite";
	sp.anims = std::map<std::string, SpriteAnimDef>();
	sp.verts = std::vector<vert2D>();
	sp.vert_indices = std::vector<int>();
	sp.anims["Spell"] = spell;
	sp.anims["Walk"] = walk;

	spriteTest = Sprite();
	spriteTest.m_shader = "DEFAULT2D";
	spriteTest.LoadAnimSprite(sp);
	//spriteTest.SetAnim("Spell");
	spriteTest.SetAnim("Walk");

	//quad.Init(200, 200, 200, 200, true, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//21 / 13

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
			}
		}break;
		case ENGINE_KEY_S:
		{
			if (Input::Get().IsKeyReleased(ENGINE_KEY_W))
			{
				Engine::get().cam->dy = 0;
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