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
		//_collision->setSphereCollision(glm::vec3(0.0f, 0.0f, 0.0f), 100);
		_collision->setBoxCollision(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 0.0f));
		_collision->SetRenderCollision(true);

		// add brain component to AI System
		addComponent(_brain);
		addComponent(_collision);

	}
}