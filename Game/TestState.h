#ifndef _TEST_STATE_H_
#define _TEST_STATE_H_

#include "State.h"
#include "Types.h"
#include "BatchRenderer.h"
#include "TextureQuad.h"
#include "Map.h"
#include "PlayerEnt.h"
#include "World.h"

class TestState : public GameEngine::State
{
    public:

        glm::mat4 model;

        GameEngine::World w;

        PlayerEnt* p;


        TestState();
        virtual ~TestState();
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
