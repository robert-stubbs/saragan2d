#include "EditorPCH.h"
#include "EditorState.h"

#include "GUI.h"

#include "DemoTool.h"
#include "TestTool.h"

using namespace GameEngine;

EditorState::EditorState() : State()
{
	_menu = Editor::MainMenu();
	_entity_manager_panel = Editor::EntityManagerTool();

	_debug_window = Editor::DebugTool();
	_resources_window = Editor::ResourcesTool();
}

EditorState::~EditorState()
{
}

void EditorState::Init()
{
	_current_tool = new Editor::TestTool();

}

void EditorState::UpdateOrth(const float& dt)
{

}

void EditorState::Render()
{
	if (GUI::GetGUI().HasInstance()) {

		GUI::Get().NewScene(1.0f / 60.0f);
		_menu.RenderUI();
		_entity_manager_panel.RenderUI();
		_debug_window.RenderUI();
		_resources_window.RenderUI();

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