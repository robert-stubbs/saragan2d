#include "EnginePCH.h"
#include "EntityManager.h"
#include "Entity.h"

namespace GameEngine
{
	EntityManager::EntityManager()
	{
	}


	EntityManager::~EntityManager()
	{
	}

	std::string EntityManager::RegisterEntity(Entity* Ent)
	{
		std::string resp = "";

		Entity* test = getEntity(Ent->m_handle);

		if (!test)
		{
			SharedEntityPtr newEnt = SharedEntityPtr(Ent);
			m_entities.push_back(newEnt);

			return Ent->m_handle;
		}
		return "";
	}

	Entity* EntityManager::getEntity(std::string EntName)
	{
		for (std::shared_ptr<Entity> ptr : m_entities) {
			if (ptr->m_handle == EntName)
			{
				return ptr.get();
			}
		}

		return nullptr;
	}

	void EntityManager::RemoveEntity(std::string Name)
	{
		for (std::vector<SharedEntityPtr>::iterator iter = m_entities.begin(); iter != m_entities.end(); iter++) {
			if ((*iter)->m_handle == Name)
			{
				//Engine::getEngine().System->RemoveComponentsByHandle(Name);
				m_entities.erase(iter);
			}
		}
	}
}