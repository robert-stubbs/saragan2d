#ifndef _MINESWEEPER_STATE_H_
#define _MINESWEEPER_STATE_H_

#include "cTile.h"
#include "GameLibrary.h"

#include "StateMachine.h"
#include "State.h"
#include "Text.h"

using namespace GameEngine;

class MinesweeperState : public State
{
private:

    float mousex;
    float mousey;

    int squareWidth;
    int squareHeight;

public:

    bool testLoaded = false;
    //Text* test = new Text();

    Tile* squares[xsize][ysize];
    std::vector<Tile*> squareList;

    MinesweeperState();
    MinesweeperState(StateMachine* fsm);
    virtual ~MinesweeperState();
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

    virtual void RevealAll();
};

#endif