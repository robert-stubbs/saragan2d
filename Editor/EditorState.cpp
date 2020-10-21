#include "EditorPCH.h"
#include "EditorState.h"

#include "GUI.h"
#include "World.h"
#include "Engine.h"

#include "DemoTool.h"
#include "TestTool.h"
#include <imgui_internal.h>

using namespace GameEngine;

EditorState::EditorState() : State()
{
	_menu = Editor::MainMenu();
	_dock = Editor::EditorDockTool();
}

EditorState::~EditorState()
{
}

void EditorState::Init()
{
	_current_tool = new Editor::TestTool();

	//if (GUI::GetGUI().HasInstance()) {

	//	GUI::Get().NewScene(1.0f / 60.0f);

	//	GUI::Get().EndAndRender();
	//}

	World* w = Engine::getWorld();
	w->LoadMap("Test Map", "");

	w->SetMap("Test Map");
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


		if (_current_tool != nullptr) {
			_current_tool->RenderUI();
		}

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

}

void EditorState::KeyUp(int Key)
{

}

void EditorState::MouseDown(int button)
{

}

void EditorState::MouseUp(int button)
{

}

void EditorState::MouseMove(float x, float y)
{

}