#include "EnginePCH.h"
#include "CollisionSystem.h"
#include "Collision.h"

#include "Component.h"

namespace GameEngine {

	CollisionSystem::CollisionSystem(bool isui, bool isanim) : System(isui, isanim)
	{
		SystemName = "COLLISION";
	}


	CollisionSystem::~CollisionSystem()
	{
	}

	void CollisionSystem::Init()
	{

	}


	void CollisionSystem::Update(float dt)
	{

	}

	void CollisionSystem::CleanUp()
	{

	}

	Component* CollisionSystem::getComponent(std::string handle)
	{
		for (iter = m_components.begin(); iter != m_components.end(); iter++)
		{
			if ((*iter)->m_handle == handle)
			{
				return (*iter).get();
			}
		}

		return nullptr;
	}

	void CollisionSystem::RemoveComponent(std::string handle)
	{
		int count = (int)m_components.size();
		for (int i = 0; i < count; i++)
		{
			Collision* comp = (Collision*)m_components.at(i).get();
			if (comp->m_handle == handle)
			{
				m_components.erase(m_components.begin() + i);
				break;
				return;
			}
		}
	}


}