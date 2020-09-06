#include "EnginePCH.h"
#include "Entity.h"
#include "Component.h"

namespace GameEngine
{
	Entity::Entity()
	{
		Parent = nullptr;
		m_components.clear();
	}

	Entity::~Entity()
	{
		m_components.clear();
	}

	bool Entity::hasComponent(std::string CompName)
	{
		for (EntityComponentPtr& comp : m_components) {
			if (comp->m_type == CompName) {
				return true;
			}
		}

		return false;
	}

	Component* Entity::getComponent(std::string CompName)
	{
		for (EntityComponentPtr& comp : m_components) {
			if (comp->m_type == CompName) {
				return comp.get();
			}
		}

		return nullptr;
	}

	void Entity::addComponent(Component* comp)
	{
		comp->SetEntity(this);
		EntityComponentPtr newComp = EntityComponentPtr(comp);
		m_components.push_back(newComp);
	}
}