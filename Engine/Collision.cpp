#include "EnginePCH.h"
#include "Collision.h"

namespace GameEngine {

	Collision::Collision()
	{
		m_type = "COLLISION";
		_type = CollisionType::BOX;
	}

	Collision::~Collision()
	{
		if (e) {
			e = nullptr;
		}
	}

	bool Collision::Init()
	{
		return true;
	}

	void Collision::Update(float dt)
	{

	}

	void Collision::CleanUp()
	{

	}

	bool Collision::doesCollide(Collision* col)
	{
		return false;
	}
}