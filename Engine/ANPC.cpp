#include "EnginePCH.h"
#include "ANPC.h"

namespace GameEngine
{
	ANPC::ANPC() : Actor()
	{
		_brain = new Brain();

	}

	ANPC::~ANPC()
	{
	}

	void ANPC::Load()
	{
		Actor::Load();

		// add brain component to AI System
		addComponent(_brain);

	}
}