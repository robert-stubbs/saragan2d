#include "EnginePCH.h"
#include "Behaviour.h"

namespace GameEngine
{
	Behaviour::Behaviour()
	{
		Ent = nullptr;
		name = "default";
		isPassive = true;
		isDummy = false;
	}
}