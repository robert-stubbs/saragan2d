#include "EnginePCH.h"
#include "Entity.h"
#include "Component.h"
#include "Engine.h"
#include "SystemManager.h"
#include "standards.h"

namespace GameEngine
{
	Entity::Entity()
	{
		Parent = nullptr;
		m_components.clear();

		m_handle = Engine::EntityMgr()->getNextID();
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

		Engine::get().System->AddComponentClass(comp->m_type,newComp.get());

	}
}