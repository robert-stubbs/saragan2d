#ifndef _ENTITY_H_
#define _ENTITY_H_

namespace GameEngine
{
	class Component;

	typedef std::shared_ptr<Component> EntityComponentPtr;

	class Entity
	{
		protected:
			std::string m_handle;
			std::string m_entityname;

			std::vector<EntityComponentPtr> m_components;

			Entity* Parent;
			std::vector<std::string> children;

			Entity();
			~Entity();

			virtual bool hasComponent(std::string CompName);
			virtual Component* getComponent(std::string CompName);
			virtual void addComponent(Component* comp);

			friend class EntityManager;
	};
}

#endif