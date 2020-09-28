#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "Entity.h"
#include "Location.h"

namespace GameEngine
{

	class Actor : public Entity
	{	
		public:
			Actor();
			virtual ~Actor();

			Location* loc;

			virtual void Load();
	};
}

#endif