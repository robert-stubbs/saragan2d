#include "GamePCH.h"
#include "EngineLibrary.h"

#include "TemplateState.h"

#include "Engine.h"
#include "Renderer.h"

TemplateState::TemplateState() {
	stateName = "GameState";
	mousex = 0;
	mousey = 0;

}

TemplateState::TemplateState(StateMachine* fsm) {
	stateName = "TemplateState";

}

TemplateState::~TemplateState() {

}

void TemplateState::Update(const float& dt) {
}

void TemplateState::Render() {

}

void TemplateState::UpdateOrth(const float& dt) {

}

void TemplateState::RenderOrth() {

}

void TemplateState::DoENTER() {

}

void TemplateState::DoEXIT() {

}

void TemplateState::KeyDown(UINT Msg, WPARAM wParam, LPARAM lParam) {

}

void TemplateState::KeyUp(UINT Msg, WPARAM wParam, LPARAM lParam) {

}

void TemplateState::MouseDown(UINT Msg, WPARAM wParam, LPARAM lParam) {

}

void TemplateState::MouseUp(UINT Msg, WPARAM wParam, LPARAM lParam) {


}

void TemplateState::MouseMove(UINT Msg, WPARAM wParam, LPARAM lParam) {

	POINT mouse;                        // Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd, &mouse);
	glm::vec3 pt = Engine::getEngine().renderer->GetWorldPos2D((int)mouse.x, (int)mouse.y, glm::mat4(1.0f), glm::mat4(1.0f));

	mousex = (float)pt.x;
	mousey = (float)pt.y;



}