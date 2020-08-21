#ifndef _AI_SYSTEM_H_
#define _AI_SYSTEM_H_

#include "System.h"
#include "Behaviour.h"
namespace GameEngine
{
	typedef std::shared_ptr<Behaviour> BehaviorComponent;
	typedef std::map<std::string, BehaviorComponent> BehaviorBank;

	class AISystem : public System
	{
	public:

		BehaviorBank Behaviours;


		AISystem(bool isui = false, bool isanim = false);
		virtual ~AISystem();

		virtual void Init();
		virtual void Update(float dt);

		virtual void Render() {};
		virtual void RenderAnim() {};
		virtual void RenderUI() {};

		virtual void CleanUp();

		Component* getComponent(std::string handle);
		virtual void RemoveComponent(std::string handle);

		void AddBehaviour(Behaviour* behaviour);
		Behaviour* getBehaviour(std::string name);
	};
}

#endif