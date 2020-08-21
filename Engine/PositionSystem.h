#ifndef _C_POSITION_SYSTEM_H_
#define _C_POSITION_SYSTEM_H_

#include "System.h"

namespace GameEngine
{
	class PositionSystem : public System
	{
	public:
		PositionSystem(bool isui = false, bool isanim = false);
		~PositionSystem();


		virtual void Init();
		virtual void Update(float dt);
		virtual void Render() {};
		virtual void RenderAnim() {};
		virtual void RenderUI() {};

		virtual void CleanUp();

		virtual void RemoveComponent(std::string handle);
		virtual Component* getComponent(std::string handle);

	};
}

#endif