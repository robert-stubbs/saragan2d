#ifndef _C_RAY_STATE_H_
#define _C_RAY_STATE_H_

#include "State.h"
#include "StateMachine.h"
#include "Line.h"

using namespace GameEngine;

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
    virtual ~RayState();
    virtual void Init();
    virtual void Update(const float& dt);
    virtual void Render();
    virtual void UpdateOrth(const float& dt);
    virtual void RenderOrth();
    virtual void DoENTER();
    virtual void DoEXIT();
    virtual void KeyDown(int Key);
    virtual void KeyUp(int Key);
    virtual void MouseDown(int button);
    virtual void MouseUp(int button);
    virtual void MouseMove(float x, float y);
};

#endif