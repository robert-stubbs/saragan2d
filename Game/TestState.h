#ifndef _TEST_STATE_H_
#define _TEST_STATE_H_

#include "Texture.h"
#include "State.h"
#include "Types.h"
#include "Sprite.h"

class TestState : public GameEngine::State
{
    public:
        GameEngine::Texture t;

        GameEngine::Sprite spriteTest;

        TestState();
        virtual ~TestState();
        virtual void Init();
        virtual void Update(const float& dt) {}
        virtual void Render() {}
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
