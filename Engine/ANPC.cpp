#include "EnginePCH.h"
#include "ANPC.h"

namespace GameEngine
{
	ANPC::ANPC() : Actor()
	{
		_brain = new Brain();
		_collision = new Collision();

	}

	ANPC::~ANPC()
	{
	}

	void ANPC::Load()
	{
		Actor::Load();

		loc->setPosition(500, 500, 0);
		_collision->setSphereCollision(glm::vec3(0.0f, 0.0f, 0.0f), 100);
		_collision->SetRenderCollision(true);

		// add brain component to AI System
		addComponent(_brain);
		addComponent(_collision);

	}
}