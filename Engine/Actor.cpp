#include "EnginePCH.h"
#include "Actor.h"

namespace GameEngine
{
	Actor::Actor() : Entity()
	{
		loc = new Location();
	}

	Actor::~Actor()
	{
	}

	void Actor::Load()
	{
		addComponent(loc);

	}
}