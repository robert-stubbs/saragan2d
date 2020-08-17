#include "GamePCH.h"
#include "MinsweeperState.h"

#include "standards.h"
#include "SafeDelete.h"

#include "StateMachine.h"
#include "State.h"
#include "cTile.h"
#include "Camera.h"
#include "Camera2D.h"
#include "Engine.h"
#include "Renderer.h"

#include "SystemManager.h"
#include "SoundSystem.h"


MinesweeperState::MinesweeperState() {
	stateName = "MinesweeperState";
	mousex = 0;
	mousey = 0;
	squareWidth = 50;
	squareHeight = 50;

	for (int x = 0; x < xsize; x++)
	{
		for (int y = 0; y < ysize; y++)
		{
			squares[x][y] = new Tile();
			squares[x][y]->Init((float)x * squareWidth,
				(float)y * squareHeight,
				(float)squareWidth,
				(float)squareHeight,
				true,
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
			);
			squareList.push_back(squares[x][y]);
		}
	}

	for (int n = 0; n < 10; ++n) {
		int numb = GetRandomNumber(0, (int)squareList.size());
		squareList[numb]->isBomb = true;
		squareList.erase(squareList.begin() + numb);
	}

	for (int x = 0; x < xsize; x++)
	{
		for (int y = 0; y < ysize; y++)
		{
			squares[x][y]->FindBombs(x, y, this);
		}
	}
}

MinesweeperState::MinesweeperState(StateMachine* fsm) {
	stateName = "MinesweeperState";

}

MinesweeperState::~MinesweeperState() {
	for (int x = 0; x < xsize; x++)
	{
		for (int y = 0; y < ysize; y++)
		{
			SAFE_DELETE(squares[x][y]);

		}
	}
}

void MinesweeperState::Init() {

	glm::mat4 temp = glm::mat4(1.0f);


	SoundSystem* smgr = (SoundSystem*)(Engine::getEngine().System->getSystem("AUDIO"));
	smgr->AddSound("C:/Assets/Sound/Sound.wav", "Bomb");

}

void MinesweeperState::Update(const float& dt) {
	Engine::getEngine().pCam->UpdateMouseLook(dt);
}

void MinesweeperState::Render() {
}

void MinesweeperState::RenderAnim() {

}

void MinesweeperState::UpdateOrth(const float& dt) {

	for (int x = 0; x < xsize; x++)
	{
		for (int y = 0; y < ysize; y++)
		{
			squares[x][y]->Update(dt);

		}
	}
}

void MinesweeperState::RenderOrth() {
	for (int x = 0; x < xsize; x++)
	{
		for (int y = 0; y < ysize; y++)
		{
			squares[x][y]->Render();

		}
	}
}

void MinesweeperState::DoENTER() {

}

void MinesweeperState::DoEXIT() {

}

void MinesweeperState::KeyDown(UINT Msg, WPARAM wParam, LPARAM lParam) {

}

void MinesweeperState::KeyUp(UINT Msg, WPARAM wParam, LPARAM lParam) {
	//cLabelEntity* ent = (cLabelEntity*)(pEngine->EntityMgr->getEntity("testingTest"));
	//if (ent != nullptr) {
	//	ent->UpdateLabel("foo bar");
	//}

}

void MinesweeperState::MouseDown(UINT Msg, WPARAM wParam, LPARAM lParam) {

}

void MinesweeperState::MouseUp(UINT Msg, WPARAM wParam, LPARAM lParam) {

	for (int x = 0; x < xsize; x++)
	{
		for (int y = 0; y < ysize; y++)
		{
			Tile* t = (squares[x][y]);

			if (t->pointInSquare(mousex, mousey)) {
				t->ProcessNeighbours(x, y, this);
				break;
			}
		}
	}
}

void MinesweeperState::MouseMove(UINT Msg, WPARAM wParam, LPARAM lParam) {

	POINT mouse;                        // Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd, &mouse);


	auto& engine = Engine::getEngine();


	glm::vec3 pt = engine.renderer->GetWorldPos2D((int)mouse.x, (int)mouse.y, engine.pCam2D->ProjectionMatrix, engine.pCam2D->ViewMatrix);

	//static char  strFPS[100] = { 0 };
	//sprintf_s(strFPS, "3D: %d,%d,%d", pt3d.x, pt3d.y, pt3d.z);
	//SetWindowText(hWnd, strFPS);

	mousex = (float)pt.x;
	mousey = (float)pt.y;

}

void MinesweeperState::RevealAll() {

	SoundSystem* smgr = (SoundSystem*)(Engine::getEngine().System->getSystem("AUDIO"));
	smgr->PlaySoundClip("Bomb");
	for (int x = 0; x < xsize; x++)
	{
		for (int y = 0; y < ysize; y++)
		{
			squares[x][y]->isRevealed = true;
		}
	}
}