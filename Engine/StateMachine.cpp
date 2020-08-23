#include "EnginePCH.h"
#include "StateMachine.h"
#include "State.h"

namespace GameEngine {
	//Constructor
	StateMachine::StateMachine()
	{
		currentState = NULL;
		delayState = "NONE";
	}

	//Destructor
	StateMachine::~StateMachine()
	{
		stateBank.clear();
	}

	//Update each tick
	void StateMachine::Update(const float& dt)
	{
		//Make sure a current state is loaded
		if (currentState == NULL) return;

		//Check if there are any delayed transition requests
		if (delayState != "NONE")
		{
			TransitionTo(delayState);
			delayState = "NONE";
		}

		//Update the current state, may trigger a transition.
		currentState->Update(dt);
	}

	void StateMachine::Render()
	{
		//Make sure a current state is loaded
		if (currentState == NULL) return;

		currentState->Render();
	}

	void StateMachine::RenderAnim()
	{
		//Make sure a current state is loaded
		if (currentState == NULL) return;

		currentState->RenderAnim();
	}

	//Update each tick
	void StateMachine::UpdateOrth(const float& dt)
	{
		//Make sure a current state is loaded
		if (currentState == NULL) return;

		//Check if there are any delayed transition requests
		if (delayState != "NONE")
		{
			TransitionTo(delayState);
			delayState = "NONE";
		}

		//Update the current state, may trigger a transition.
		currentState->UpdateOrth(dt);
	}

	void StateMachine::RenderOrth()
	{
		//Make sure a current state is loaded
		if (currentState == NULL) return;

		currentState->RenderOrth();
	}

	void StateMachine::KeyDown(int Key)
	{
		currentState->KeyDown(Key);
	}

	void StateMachine::KeyUp(int Key)
	{
		currentState->KeyUp(Key);
	}

	void StateMachine::MouseDown(int Button)
	{
		currentState->MouseDown(Button);
	}

	void StateMachine::MouseUp(int Button)
	{
		currentState->MouseUp(Button);
	}

	void StateMachine::MouseMove(float x, float y)
	{
		currentState->MouseMove(x, y);
	}

	//Called to transition to another state
	//@param stateName the name of the state to transition to
	void StateMachine::TransitionTo(std::string stateName)
	{
		//cErrorLogger::Log().WriteToConsole(">> Start of Transition To ", false);
		//cErrorLogger::Log().WriteToConsole(stateName.c_str());

		//Find the named state
		State* goToState = NULL;
		if (stateBank.size() == 0)
		{
			//cErrorLogger::Log().WriteToConsole("**********************************************");
			//cErrorLogger::Log().WriteToConsole("**************StateBank is Empty**************");
			//cErrorLogger::Log().WriteToConsole("**********************************************");
		}

		for (iter = stateBank.begin(); iter != stateBank.end(); ++iter)

			if ((*iter)->stateName == stateName)
			{
				goToState = iter->get();
				//cErrorLogger::Log().WriteToConsole(">> Info: Transition Accepted");
			}
		//Error, trying to transition to a non-existant state
		if (goToState == NULL)
		{
			//Print an error here, or assert if you want
			return;
		}

		currentState->DoEXIT();
		goToState->DoENTER();
		currentState = goToState;
		//cErrorLogger::Log().WriteToConsole(">> Info: Transition Successful");
	}

	//Transition to another state (delayed until beginning of next update)
	//@param stateName the name of the state to transition to
	void StateMachine::DelayTransitionTo(std::string stateName)
	{
		delayState = stateName;
	}

	//Add a state to the bank, optionally make it the current state
	//@param newState the new state to add to the state machine
	//@param makeCurrent is this new state the current state?
	void StateMachine::AddState(State* newState, bool makeCurrent)
	{
		//cErrorLogger::Log().WriteToConsole(_T("> Info: Adding State\n"));
		  //Add this state to the FSM
		std::shared_ptr<State> newStatePtr(newState);

		stateBank.push_back(newStatePtr);
		//Make this the current state?
		if (makeCurrent)
		{
			if (currentState) {
				currentState->DoEXIT();
			}
			newState->DoENTER();
			currentState = newState;
		}
	}

	//What is the name of the current state?
	std::string StateMachine::GetState()
	{

		if (currentState == NULL) return "##### No State #####";

		return currentState->stateName;
	}
}