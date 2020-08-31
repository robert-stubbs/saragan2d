#ifndef _TEST_STATE_H_
#define _TEST_STATE_H_

#include "Texture.h"
#include "State.h"
#include "Types.h"
#include "Sprite.h"
#include "BatchRenderer.h"
#include "TextureQuad.h"

class TestState : public GameEngine::State
{
    public:
        GameEngine::Texture t;

        //GameEngine::Sprite spriteTest;
        GameEngine::BatchRenderer b;
        GameEngine::TextureQuad q;

        GameEngine::TextureQuad quads[10][10];

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
