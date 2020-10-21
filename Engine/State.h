#ifndef _STATE_H_
#define _STATE_H_

namespace GameEngine {
    class StateMachine;

    class State
    {
        public:
            State() {};
            State(StateMachine* fsm) {};
            virtual ~State() {};
            virtual void Init() = 0;
            virtual void Update(const float& dt) = 0;
            virtual void Render() = 0;
            virtual void UpdateOrth(const float& dt) = 0;
            virtual void RenderOrth() = 0;
            virtual void RenderEditorUI() {};
            virtual void DoENTER() = 0;
            virtual void DoEXIT() = 0;
            virtual void KeyDown(int Key) = 0;
            virtual void KeyUp(int Key) = 0;
            virtual void MouseDown(int button) = 0;
            virtual void MouseUp(int button) = 0;
            virtual void MouseMove(float x, float y) = 0;

            std::string stateName;  //used to switch between states
            StateMachine* fsm;
        protected:
    };
}


#endif
