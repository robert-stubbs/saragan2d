#include "EditorPCH.h"
#include "EditorState.h"

#include "GUI.h"
#include "World.h"
#include "Engine.h"
#include "ANPC.h"

#include "DemoTool.h"
#include "TestTool.h"
#include <imgui_internal.h>

using namespace GameEngine;

EditorState::EditorState() : State()
{
	_menu = Editor::MainMenu();
	_dock = Editor::EditorDockTool();
	_dock.Init();
}

EditorState::~EditorState()
{
}

void EditorState::Init()
{
	_current_tool = new Editor::TestTool();

	World* w = Engine::getWorld();

	//w->LoadMap("Test Map", "");

	//w->SetMap("Test Map");

	/*NPC = new GameEngine::ANPC();
	NPC->m_handle = "NPC_1";
	Engine::EntityMgr()->RegisterEntity(NPC, true);*/
}

void EditorState::UpdateOrth(const float& dt)
{

}

void EditorState::Render()
{
}

void EditorState::RenderEditorUI() 
{
	if (GUI::GetGUI().HasInstance()) {

		GUI::Get().NewScene(1.0f / 60.0f);

		_menu.RenderUI();
		_dock.RenderUI();


		GUI::Get().EndAndRender();
	}

}

void EditorState::RenderOrth()
{
}

void EditorState::DoENTER()
{

}

void EditorState::DoEXIT()
{

}

void EditorState::KeyDown(int Key)
{
	Camera2D* cam = Engine::get().current_cam;
	switch (Input::Get().GetKey(Key))
	{
		case ENGINE_KEY_A:
		{
			cam->dx = -30;
		}break;
		case ENGINE_KEY_D:
		{
			cam->dx = 30;
		}break;
		case ENGINE_KEY_W:
		{
			cam->dy = -30;
		}break;
		case ENGINE_KEY_S:
		{
			cam->dy = 30;
		}break;
		case ENGINE_KEY_1:
		{
		}break;
	}
}

void EditorState::KeyUp(int Key)
{
	Camera2D* cam = Engine::get().current_cam;
	switch (Input::Get().GetKey(Key))
	{
	case ENGINE_KEY_A:
	{
		if (Input::Get().IsKeyReleased(ENGINE_KEY_D))
		{
			cam->dx = 0;
		}
	}break;
	case ENGINE_KEY_D:
	{
		if (Input::Get().IsKeyReleased(ENGINE_KEY_A))
		{
			cam->dx = 0;
		}
	}break;
	case ENGINE_KEY_W:
	{
		if (Input::Get().IsKeyReleased(ENGINE_KEY_S))
		{
			cam->dy = 0;
		}
	}break;
	case ENGINE_KEY_S:
	{
		if (Input::Get().IsKeyReleased(ENGINE_KEY_W))
		{
			cam->dy = 0;
		}
	}break;
	}
}

void EditorState::MouseDown(int button)
{
	_dock.MouseDown(button);
}

void EditorState::MouseUp(int button)
{
	_dock.MouseUp(button);
}

void EditorState::MouseMove(float x, float y)
{
	_dock.MouseMove(x, y);

}

void EditorState::MouseScroll(float xoffset, float yoffset)
{
	Camera2D* cam = Engine::get().current_cam;
	cam->AdjustZoom(yoffset);
}