#ifndef _A_NPC_H_
#define _A_NPC_H_

#include "Actor.h"
#include "Brain.h"
#include "Collision.h"

namespace GameEngine
{

	class ANPC : public Actor
	{
		public:
			Brain* _brain;
			Collision* _collision;

			ANPC();
			virtual ~ANPC();

			virtual void Load();
	};
}

#endif