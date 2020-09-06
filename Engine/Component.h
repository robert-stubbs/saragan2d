#ifndef _COMPONENT_H_
#define _COMPONENT_H_

namespace GameEngine
{
	class Entity;

	class Component
	{
		public:
			std::string m_type;
			std::string m_handle;
			std::string m_shader;
			bool loaded = false;

			Entity* e;

			Component();
			virtual ~Component();

			virtual bool Init() { return true; };

			virtual void Update(float dt) {};

			virtual void Render() {};

			virtual void CleanUp() {};

			inline Entity* GetEntity() { return e; }
			inline void SetEntity(Entity* ent) { e = ent; }
	};
}

#endif