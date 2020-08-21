#include "EnginePCH.h"
#include "Brain.h"

#include "Brain.h"

#include "cErrorLogger.h"
#include "Engine.h"
#include "SystemManager.h"
#include "AISystem.h"

namespace GameEngine
{
	Brain::Brain()
	{
		States.clear();
		Passives.clear();
		m_type = "brain";
	}


	Brain::~Brain()
	{
	}

	//##########################################################################
	// Behaviours
	//##########################################################################

	void Brain::AddBehaviour(std::string behaviour)
	{
		AISystem* sysAI = (AISystem*)Engine::getEngine().System->getSystem("AI");
		Behaviour* state = sysAI->getBehaviour(behaviour);

		if (state->isDummy)
		{
			return;
		}

		if (state->isPassive)
		{
			return AddPassive(behaviour);
		}

		return AddState(behaviour);
	}

	void Brain::AddPassive(std::string behaviour)
	{
		bool found = false;

		for (size_t i = 0; i < Passives.size(); i++)
		{
			if (Passives.at(i) == name)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			Passives.push_back(behaviour);
		}
	}

	void Brain::AddState(std::string behaviour)
	{
		std::string behave = States[behaviour];

		if (behave.empty() || behave == "")
		{
			States[behaviour] = behaviour;
		}
	}

	Behaviour* Brain::getPassive(std::string name)
	{


		AISystem* sysAI = (AISystem*)Engine::getEngine().System->getSystem("AI");
		for (PassiveIter = Passives.begin(); PassiveIter != Passives.end(); PassiveIter++) {
			if ((*PassiveIter) == name)
			{
				return sysAI->getBehaviour(name);
			}
		}

		return nullptr;
	}

	Behaviour* Brain::getState(std::string name)
	{
		std::string behave = States[name];

		if (!behave.empty() || behave != "")
		{
			AISystem* sysAI = (AISystem*)Engine::getEngine().System->getSystem("AI");
			return sysAI->getBehaviour(behave);
		}
		return nullptr;
	}

	//##########################################################################

	void Brain::changeState(std::string name)
	{
		if (currentState.size() == 0) {
			Behaviour* state = getState(name);
			if (state != nullptr && !state->isPassive)
			{
				currentState = name;
				state->Ent = ent;
				state->DoEnter();
			}
		}
		else {
			Behaviour* current = nullptr;
			Behaviour* state = nullptr;

			if (currentState != name)
			{
				state = getState(name);
				current = getState(currentState);

				if (state != nullptr && current != nullptr)
				{
					current->Ent = ent;
					current->DoExit();
					state->Ent = ent;
					state->DoEnter();

					currentState = name;
				}
			}
		}
	}


	bool Brain::Init()
	{

		cErrorLogger::Er->WriteToConsole("> Initialized Brain\n");
		return true;
	}

	void Brain::Update(float dt)
	{
		if (currentState.empty())
		{
			return;
		}

		for (size_t i = 0; i < Passives.size(); i++)
		{
			Behaviour* passive = getPassive(Passives.at(i));
			passive->Ent = ent;
			passive->Update(dt);
		}

		Behaviour* current = getState(currentState);
		current->Ent = ent;
		current->Update(dt);
	}

	void Brain::Render()
	{
		if (currentState.empty())
		{
			return;
		}

		for (size_t i = 0; i < Passives.size(); i++)
		{
			Behaviour* passive = getPassive(Passives.at(i));
			passive->Ent = ent;
			passive->Render();
		}

		Behaviour* current = getState(currentState);
		current->Ent = ent;
		current->Render();
	}

	bool Brain::handleMessage(SystemMessage msg)
	{
		if (currentState.empty())
		{
			return false;
		}

		bool handled = false;

		for (size_t i = 0; i < Passives.size(); i++)
		{
			Behaviour* passive = getPassive(Passives.at(i));
			passive->Ent = ent;
			passive->handleMessage(msg);
		}

		Behaviour* current = getState(currentState);
		current->Ent = ent;
		handled = current->handleMessage(msg);

		return handled;
	}

	void Brain::CleanUp()
	{

	}
}