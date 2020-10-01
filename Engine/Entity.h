#ifndef _ENTITY_H_
#define _ENTITY_H_

namespace GameEngine
{
	class Component;

	typedef std::shared_ptr<Component> EntityComponentPtr;

	class Entity
	{
		public:
			std::string m_handle;
			std::string m_entityname;

			Entity();
			virtual ~Entity();

			virtual void Load() {};

			std::vector<EntityComponentPtr> m_components;

			Entity* Parent;
			std::vector<std::string> children;

			virtual bool hasComponent(std::string CompName);
			virtual Component* getComponent(std::string CompName);
			virtual void addComponent(Component* comp);

			virtual void hasCollided(Component* comp) {}
	};
}

#endif