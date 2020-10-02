#include "GamePCH.h"
#include "PlayerEnt.h"

#include "Engine.h"
#include "System.h"
#include "SystemManager.h"

PlayerEnt::PlayerEnt() : GameEngine::Actor() {

	m_entityname = "PlayerEntity";
	Parent = nullptr;

	speed = 0.20f;

	dx = 0;
	dy = 0;
	dz = 0;

	_lastpos = glm::vec3(1.0f, 1.0f, 1.0f);

	cam = new Camera();
	sprite = new Sprite();
	c = new Collision();
	t = Texture();
}

PlayerEnt::~PlayerEnt() {


}

void PlayerEnt::Load() {

	Actor::Load();

	cam->SetUpCamera((float)Engine::get().RenderWidth, (float)Engine::get().RenderHeight);
	addComponent(cam);

	// Add Texture
	if (t.LoadFile(Engine::get().asset_dir + "Textures/testsprite.png", TEXTURETYPES::SARAGAN_PNG))
	{
		t.GenerateAlphaBuffer();
	}

	// Add Sprite
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
	sp.anims["WalkDown"] = walk;
	sp.anims["WalkLeft"] = walkleft;
	sp.anims["WalkRight"] = walkright;
	sp.anims["WalkUp"] = walkup;
	sp.anims["Spell"] = spell;

	sprite->m_shader = "DEFAULT2D";
	sprite->LoadAnimSprite(sp);
	sprite->SetAnim("Idle");

	addComponent(sprite);

	c->setSphereCollision(glm::vec3(idle.frame_width / 2.0f, idle.frame_height / 2.0f, 1.0f), (idle.frame_width / 2.0f));
	c->SetRenderCollision(true);

	addComponent(c);

}

void PlayerEnt::Update(float dt)
{

	Location* loc = (Location*)getComponent("LOCATION");
	if (loc != nullptr) {
		// set look at on camera to position x,y,z		
		glm::vec3& pos = loc->getPosition();

		// do not alter this
		_lastpos = glm::vec3(pos.x, pos.y, pos.z);

		pos.x += (dx)*speed;
		pos.y += (dy)*speed;
	}

}

void PlayerEnt::SetState(states st)
{
	switch (st)
	{	
		case states::IDLE:
		{
			sprite->SetAnim("Idle");
		} break;
		case states::WALK_LEFT:
		{
			sprite->SetAnim("WalkLeft");
		} break;
		case states::WALK_RIGHT:
		{
			sprite->SetAnim("WalkRight");
		} break;
		case states::WALK_UP:
		{
			sprite->SetAnim("WalkUp");
		} break;
		case states::WALK_DOWN:
		{
			sprite->SetAnim("WalkDown");
		} break;
		case states::SPELL:
		{
			sprite->SetAnim("Spell");
		} break;

	default:
		sprite->SetAnim("Idle");
		break;
	}
}

void PlayerEnt::hasCollided(Component* comp)
{
	if (comp->m_type == "COLLISION") {
		//Location* loc = (Location*)getComponent("LOCATION");
		//loc->setPosition(_lastpos.x, _lastpos.y, _lastpos.z);
	}
}