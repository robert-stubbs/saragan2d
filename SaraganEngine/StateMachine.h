#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

class State;

typedef std::shared_ptr<State> SharedPtr;
typedef std::vector< SharedPtr > StateBank;

class StateMachine
{
public:
    StateMachine();
    ~StateMachine();
    void Update(const float& dt);
    void Render();

    void RenderAnim();

    void UpdateOrth(const float& dt);
    void RenderOrth();


    void TransitionTo(std::string stateName);
    void DelayTransitionTo(std::string stateName);
    void AddState(State* newState, bool makeCurrent);
    void KeyDown(UINT Msg, WPARAM wParam, LPARAM lParam);
    void KeyUp(UINT Msg, WPARAM wParam, LPARAM lParam);
    void MouseDown(UINT Msg, WPARAM wParam, LPARAM lParam);
    void MouseUp(UINT Msg, WPARAM wParam, LPARAM lParam);
    void MouseMove(UINT Msg, WPARAM wParam, LPARAM lParam);


    std::string GetState();

public:
    State* currentState;
    std::string delayState;

    //Bank to house list of states
    StateBank stateBank;
    std::vector< SharedPtr >::iterator iter;
};

#endif