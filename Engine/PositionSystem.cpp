#include "EnginePCH.h"
#include "PositionSystem.h"
#include "Location.h"

#include "Component.h"

namespace GameEngine {

	PositionSystem::PositionSystem(bool isui, bool isanim) : System(isui, isanim)
	{
		SystemName = "POSITION";
	}


	PositionSystem::~PositionSystem()
	{
	}

	void PositionSystem::Init()
	{

	}


	void PositionSystem::Update(float dt)
	{

	}

	void PositionSystem::CleanUp()
	{

	}

	Component* PositionSystem::getComponent(std::string handle)
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

	void PositionSystem::RemoveComponent(std::string handle)
	{
		int count = (int)m_components.size();
		for (int i = 0; i < count; i++)
		{
			Location* comp = (Location*)m_components.at(i).get();
			if (comp->m_handle == handle)
			{
				m_components.erase(m_components.begin() + i);
				break;
				return;
			}
		}
	}


}