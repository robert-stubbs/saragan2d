#ifndef _MINESWEEPER_STATE_H_
#define _MINESWEEPER_STATE_H_

#include "GameLibrary.h"

#include "cTile.h"

#include "StateMachine.h"
#include "State.h"
#include "Text.h"

class Tile;
class cCube;

class MinesweeperState : public State
{
private:

    float mousex;
    float mousey;

    int squareWidth;
    int squareHeight;

public:

    bool testLoaded = false;
    Text* test = new Text();

    Tile* squares[xsize][ysize];
    std::vector<Tile*> squareList;

    MinesweeperState();
    MinesweeperState(StateMachine* fsm);
    virtual ~MinesweeperState();
    virtual void Init();
    virtual void Update(const float& dt);
    virtual void Render();
    virtual void RenderAnim();
    virtual void UpdateOrth(const float& dt);
    virtual void RenderOrth();
    virtual void DoENTER();
    virtual void DoEXIT();
    virtual void KeyDown(UINT Msg, WPARAM wParam, LPARAM lParam);
    virtual void KeyUp(UINT Msg, WPARAM wParam, LPARAM lParam);
    virtual void MouseDown(UINT Msg, WPARAM wParam, LPARAM lParam);
    virtual void MouseUp(UINT Msg, WPARAM wParam, LPARAM lParam);
    virtual void MouseMove(UINT Msg, WPARAM wParam, LPARAM lParam);

    virtual void RevealAll();
};

#endif