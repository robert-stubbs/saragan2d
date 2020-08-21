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
            virtual void RenderAnim() = 0;
            virtual void UpdateOrth(const float& dt) = 0;
            virtual void RenderOrth() = 0;
            virtual void DoENTER() = 0;
            virtual void DoEXIT() = 0;
            virtual void KeyDown(UINT Msg, WPARAM wParam, LPARAM lParam) = 0;
            virtual void KeyUp(UINT Msg, WPARAM wParam, LPARAM lParam) = 0;
            virtual void MouseDown(UINT Msg, WPARAM wParam, LPARAM lParam) = 0;
            virtual void MouseUp(UINT Msg, WPARAM wParam, LPARAM lParam) = 0;
            virtual void MouseMove(UINT Msg, WPARAM wParam, LPARAM lParam) = 0;

            std::string stateName;  //used to switch between states
            StateMachine* fsm;
        protected:
    };
}


#endif
