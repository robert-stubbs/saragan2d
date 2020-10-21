#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

namespace GameEngine {
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


        void UpdateOrth(const float& dt);
        void RenderOrth();

        void RenderEditorUI();

        void TransitionTo(std::string stateName);
        void DelayTransitionTo(std::string stateName);
        void AddState(State* newState, bool makeCurrent);
        void KeyDown(int Key);
        void KeyUp(int Key);
        void MouseDown(int button);
        void MouseUp(int button);
        void MouseMove(float x, float y);


        std::string GetState();

    public:
        State* currentState;
        std::string delayState;

        //Bank to house list of states
        StateBank stateBank;
        std::vector< SharedPtr >::iterator iter;
    };
}
#endif