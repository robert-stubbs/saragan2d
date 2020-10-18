#include "EditorPCH.h"
#include "EditorState.h"


#include "DemoTool.h"
#include "TestTool.h"

using namespace GameEngine;

EditorState::EditorState() : State()
{

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

	if (_current_tool != nullptr) {
		_current_tool->RenderUI();
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