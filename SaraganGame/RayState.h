#ifndef _C_RAY_STATE_H_
#define _C_RAY_STATE_H_

#include "State.h"
#include "StateMachine.h"

class Line;

class RayState : public State
{
private:
    Line* line2;
    std::vector<Line> mouseLines;


    std::vector<Line> hitLines;



    float mousex;
    float mousey;

public:
    RayState();
    RayState(StateMachine* fsm);
    virtual ~RayState();
    virtual void Init() {};
    virtual void Update(const float& dt);
    virtual void Render();
    virtual void RenderAnim() {};
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