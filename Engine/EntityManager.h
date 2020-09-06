#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "Entity.h"

namespace GameEngine {


	typedef std::shared_ptr<Entity> SharedEntityPtr;

	class EntityManager
	{
	public:
		std::vector<SharedEntityPtr> m_entities;

		EntityManager();
		~EntityManager();

		std::string RegisterEntity(Entity* Ent);

		Entity* getEntity(std::string EntName);
		void RemoveEntity(std::string Name);
	};
}

#endif