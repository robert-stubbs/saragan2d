#ifndef _PLAYER_ENT_H_
#define _PLAYER_ENT_H_

#include "Entity.h"
#include "Location.h"
#include "Camera.h"
#include "Sprite.h"
#include "Texture.h"

using namespace GameEngine;

class PlayerEnt : public Entity
{
	private:
		Location* loc;
		Camera* cam;
		Sprite* sprite;

		Texture t;
	protected:


	public:
		PlayerEnt();
		~PlayerEnt();


		virtual void Load() override;


};

#endif

