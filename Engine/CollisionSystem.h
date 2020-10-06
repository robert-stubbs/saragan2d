#ifndef _COLLISION_SYSTEM_H_
#define _COLLISION_SYSTEM_H_

#include "System.h"

namespace GameEngine {

	class CollisionSystem : public System
	{
	public:
		CollisionSystem(bool isui = false, bool isanim = false);
		~CollisionSystem();


		virtual void Init();
		virtual void Update(float dt);
		virtual void Render();

		virtual void CleanUp();

		virtual void RemoveComponent(std::string handle);
		virtual Component* getComponent(std::string handle);

	};
}

#endif