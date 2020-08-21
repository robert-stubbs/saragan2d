#ifndef _BRAIN_H_
#define _BRAIN_H_

#include "Component.h"
#include "Behaviour.h"

namespace GameEngine
{
	class Brain : public Component
	{

	public:

		std::string name;

		std::string currentState;

		Brain();
		~Brain();

		std::vector<std::string> Passives;
		std::vector<std::string>::iterator PassiveIter;

		std::map<std::string, std::string> States;

		void AddBehaviour(std::string behaviour);
		void AddPassive(std::string  behaviour);
		void AddState(std::string behaviour);

		Behaviour* getPassive(std::string name);
		Behaviour* getState(std::string name);

		virtual void changeState(std::string name);

		virtual bool Init();

		virtual void Update(float dt);
		virtual void Render();
		virtual void RenderAnim() {};
		virtual bool handleMessage(SystemMessage msg);

		virtual void CleanUp();


	};
}

#endif