#ifndef _C_GAME_STATE_H_
#define _C_GAME_STATE_H_

#include "State.h"
#include "StateMachine.h"

class TemplateState : public State
{
private:

    float mousex;
    float mousey;


public:
    TemplateState();
    TemplateState(StateMachine* fsm);
    virtual ~TemplateState();
    virtual void Update(const float& dt);
    virtual void Render();
    virtual void UpdateOrth(const float& dt);
    virtual void RenderOrth();
    virtual void DoENTER();
    virtual void DoEXIT();
    virtual void KeyDown(UINT Msg, WPARAM wParam, LPARAM lParam);
    virtual void KeyUp(UINT Msg, WPARAM wParam, LPARAM lParam);
    virtual void MouseDown(UINT Msg, WPARAM wParam, LPARAM lParam);
    virtual void MouseUp(UINT Msg, WPARAM wParam, LPARAM lParam);
    virtual void MouseMove(UINT Msg, WPARAM wParam, LPARAM lParam);
};

#endif