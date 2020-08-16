#include "EnginePCH.h"
#include "EntityManager.h"

#include "Entity.h"
#include "Engine.h"
#include "SystemManager.h"

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
		SharedEntityPtr newEntity(Ent);
		m_entities[Ent->m_handle] = newEntity;
		return Ent->m_handle;
	}
	return "";
}

Entity* EntityManager::getEntity(std::string EntName)
{
	for (iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		if (iter->first == EntName)
		{
			return iter->second.get();
		}
	}
	return nullptr;
}

void EntityManager::RemoveEntity(std::string Name)
{

	for (iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		if (iter->first == Name)
		{
			
			// remove all components first
			Engine::getEngine().System->RemoveComponentsByHandle(Name);

			Entity* ent = (*iter).second.get();
			for (size_t i = 0; i < ent->m_components.size(); i++)
			{
				ent->m_components.erase(ent->m_components.begin() + i);
			}
			ent->m_components.clear();
			m_entities.erase(iter);

			return;
		}
	}
}