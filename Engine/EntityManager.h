#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_
namespace GameEngine
{
	class Entity;

	typedef std::shared_ptr<Entity> SharedEntityPtr;
	typedef std::map<std::string, SharedEntityPtr > EntityBank;

	class EntityManager
	{
	public:
		EntityBank m_entities;
		EntityBank::iterator iter;

		EntityManager();
		~EntityManager();

		std::string RegisterEntity(Entity* Ent);

		Entity* getEntity(std::string EntName);
		void RemoveEntity(std::string Name);
	};
}

#endif