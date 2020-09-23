#include "EnginePCH.h"
#include "Component.h"

namespace GameEngine
{
	Component::Component()
	{
	}

	Component::~Component()
	{
		if (e) {
			e = nullptr;
		}
	}
}