#ifndef _PLAYER_ENT_H_
#define _PLAYER_ENT_H_

#include "Actor.h"
#include "Location.h"
#include "Camera.h"
#include "Sprite.h"
#include "Texture.h"
#include "Collision.h"

using namespace GameEngine;

enum class states {
	IDLE = 0,
	WALK_LEFT,
	WALK_RIGHT,
	WALK_UP,
	WALK_DOWN,
	SPELL
};

class PlayerEnt : public Actor
{
	private:
		Camera* cam;
		Sprite* sprite;
		Collision* c;

		Texture t;


		float speed;
	protected:

	public:
		float dx; //how much we strafe on x
		float dy; //how much we walk on y
		float dz; //how much we walk on z

		PlayerEnt();
		~PlayerEnt();


		virtual void Load() override;
		inline Camera* getCam() { return cam; };

		virtual void Update(float dt);

		virtual void SetState(states st);
};

#endif

