#ifndef _SPRITE_SYSTEM_H_
#define _SPRITE_SYSTEM_H_

#include "System.h"

namespace GameEngine {

	class SpriteSystem : public System
	{
	public:
		SpriteSystem(bool isui = false, bool isanim = false);
		~SpriteSystem();


		virtual void Init();
		virtual void Update(float dt);
		virtual void Render() {};
		virtual void RenderAnim() {};
		virtual void RenderUI();

		virtual void CleanUp();

		virtual void RemoveComponent(std::string handle);
		virtual Component* getComponent(std::string handle);

	};
}

#endif