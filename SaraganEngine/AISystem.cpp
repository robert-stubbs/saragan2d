#include "EnginePCH.h"
#include "AISystem.h"

#include "System.h"
#include "Brain.h"
#include "Behaviour.h"

AISystem::AISystem(bool isui, bool isanim) : System(isui, isanim) {

	SystemName = "AI";
	m_components.clear();
}


AISystem::~AISystem()
{
}

void AISystem::Init()
{

}


void AISystem::Update(float dt)
{
	for (size_t i = 0; i < m_components.size(); i++)
	{
		Component* brain = m_components.at(i).get();
		if (brain != nullptr)
		{
			brain->Update(dt);
		}
	}
}

void AISystem::CleanUp()
{
	m_components.clear();
}

Component* AISystem::getComponent(std::string handle)
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

void AISystem::RemoveComponent(std::string handle)
{


}

void AISystem::AddBehaviour(Behaviour* behaviour)
{
	Behaviour* behave = getBehaviour(behaviour->name);

	if (behave == nullptr)
	{
		BehaviorComponent com(behaviour);
		Behaviours[behaviour->name] = com;
	}
}

Behaviour* AISystem::getBehaviour(std::string name)
{
	BehaviorComponent behave = Behaviours[name];

	if (behave.get() != nullptr)
	{
		return behave.get();
	}

	return nullptr;
}
