#include "GamePCH.h"
#include "GameLibrary.h"
#include "RayState.h"

#include "Engine.h"
#include "Renderer.h"
#include "Line.h"



RayState::RayState() {
	stateName = "RayState";
	mousex = 0;
	mousey = 0;
		
	Line top = Line();
	top.Init(0.1f, 0.1f, (GLfloat)Engine::getEngine().width, 0.1f);
	hitLines.push_back(top);

	Line bottom = Line();
	bottom.Init(0.1f, (GLfloat)Engine::getEngine().height - 1, (GLfloat)Engine::getEngine().width, (GLfloat)Engine::getEngine().height - 1);
	hitLines.push_back(bottom);

	Line left = Line();
	left.Init(0.1f, 0.1f, 0.1f, (GLfloat)Engine::getEngine().height);
	hitLines.push_back(left);

	Line right = Line();
	right.Init((GLfloat)Engine::getEngine().width, 0.1f, (GLfloat)Engine::getEngine().width, (GLfloat)Engine::getEngine().height);
	hitLines.push_back(right);

	for (size_t i = 0; i < 10; i++)
	{
		float x = (float)(rand() % ((int)Engine::getEngine().width + 1) + 0);
		float y = (float)(rand() % ((int)Engine::getEngine().height + 1) + 0);
		float x1 = (float)(rand() % ((int)Engine::getEngine().width + 1) + 0);
		float y1 = (float)(rand() % ((int)Engine::getEngine().height + 1) + 0);

		Line random = Line();
		random.Init(x, y, x1, y1);
		hitLines.push_back(random);
	}


	for (size_t i = 0; i < 360; i += 3)
	{
		Line current = Line();
		current.Init(mousex, mousey, (float)DEG2RAD(i));
		mouseLines.push_back(current);
	}
}

RayState::RayState(StateMachine* fsm) {
	stateName = "GameState";

}

RayState::~RayState() {

}

void RayState::Update(const float& dt) {
}

void RayState::Render() {

}

void RayState::UpdateOrth(const float& dt) {

	for (size_t i = 0; i < hitLines.size(); i++)
	{
		hitLines[i].Update(dt);
	}

	for (size_t i = 0; i < mouseLines.size(); i++)
	{
		mouseLines[i].Update(dt);
	}
}

void RayState::RenderOrth() {

	for (size_t i = 0; i < hitLines.size(); i++)
	{
		hitLines[i].Render();
	}

	for (size_t i = 0; i < mouseLines.size(); i++)
	{
		mouseLines[i].Render();
	}
}

void RayState::DoENTER() {

}

void RayState::DoEXIT() {

}

void RayState::KeyDown(UINT Msg, WPARAM wParam, LPARAM lParam) {

}

void RayState::KeyUp(UINT Msg, WPARAM wParam, LPARAM lParam) {

}

void RayState::MouseDown(UINT Msg, WPARAM wParam, LPARAM lParam) {

}

void RayState::MouseUp(UINT Msg, WPARAM wParam, LPARAM lParam) {

}

void RayState::MouseMove(UINT Msg, WPARAM wParam, LPARAM lParam) {

	POINT mouse;                        // Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd, &mouse);
	glm::vec3 pt = Engine::getEngine().renderer->GetWorldPos2D((int)mouse.x, (int)mouse.y, glm::mat4(1.0f), glm::mat4(1.0f));

	mousex = (float)pt.x;
	mousey = (float)pt.y;


	for (size_t i = 0; i < mouseLines.size(); i++)
	{
		mouseLines[i].UpdatePos(mousex, mousey, hitLines);
		mouseLines[i].hasUpdate = true;
	}

	//pEngine->UpdateLine(wPos.x,wPos.y,wPos.z);
}