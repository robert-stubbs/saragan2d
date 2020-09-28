#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

namespace GameEngine {

	class Entity;

	typedef std::shared_ptr<Entity> EntityPtr;

	class EntityManager
	{
		public:
			std::vector<EntityPtr> m_entities;

			int ids = 0;

			EntityManager();
			~EntityManager();

			std::string RegisterEntity(Entity* Ent, bool load = false);

			Entity* getEntity(std::string EntName);
			void RemoveEntity(std::string Name);

			inline int getNextID() { ids++; return ids; }
	};
}

#endif