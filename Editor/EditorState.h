#ifndef _TEST_STATE_H_
#define _TEST_STATE_H_

#include "State.h"
#include "BaseTool.h"
#include "MainMenu.h"
#include "EditorDockTool.h"

class EditorState : public GameEngine::State
{
public:
    Editor::MainMenu _menu;
    Editor::EditorDockTool _dock;

    Editor::BaseTool* _current_tool;

    EditorState();
    virtual ~EditorState();
    virtual void Init();
    virtual void Update(const float& dt) {}
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
