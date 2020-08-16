#include "EnginePCH.h"
#include "Entity.h"

#include "Component.h"


Entity::Entity()
{
	hasPosition = false;
	hasCamera = false;
	hasCollision = false;
	hasPhysics = false;
	hasInput = false;
	hasGameData = false;
	hasModel = false;
	hasAnimModel = false;
	hasSound = false;
	hasSprite = false;
	hasBrain = false;

	Parent = nullptr;

	m_components.clear();
}

Entity::~Entity()
{

}

bool Entity::hasComponent(std::string CompName)
{
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		if ((*iter)->m_type == CompName)
		{
			return true;
		}
	}

	return false;
}

Component* Entity::getComponent(std::string CompName)
{
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		if ((*iter)->m_type == CompName)
		{
			return (*iter).get();
		}
	}
	return nullptr;
}

void Entity::addComponent(Component* comp)
{
	comp->ent = this;
	EntityComponentPtr newComp(comp);
	m_components.push_back(newComp);
}