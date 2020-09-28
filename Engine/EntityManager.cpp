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

	std::string EntityManager::RegisterEntity(Entity* Ent, bool load)
	{
		std::string resp = "";

		Entity* test = getEntity(Ent->m_handle);

		if (test == nullptr)
		{
			EntityPtr newEnt = EntityPtr(Ent);

			if (load) {
				newEnt->Load();
			}

			m_entities.push_back(newEnt);

			return Ent->m_handle;
		}
		return "";
	}

	Entity* EntityManager::getEntity(std::string EntName)
	{
		for (EntityPtr ptr : m_entities) {
			if (ptr->m_entityname == EntName)
			{
				return ptr.get();
			}
		}

		return nullptr;
	}

	void EntityManager::RemoveEntity(std::string Name)
	{
		for (std::vector<EntityPtr>::iterator iter = m_entities.begin(); iter != m_entities.end(); iter++) {
			if ((*iter)->m_entityname == Name)
			{
				//Engine::getEngine().System->RemoveComponentsByHandle(Name);
				m_entities.erase(iter);
			}
		}
	}
}