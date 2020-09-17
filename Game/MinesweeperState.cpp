#include "GamePCH.h"
#include "MinesweeperState.h"

#include "SafeDelete.h"
#include "standards.h"

#include "StateMachine.h"
#include "State.h"
#include "cTile.h"
#include "Camera2D.h"
#include "Engine.h"
#include "Renderer.h"

//#include "SystemManager.h"
//#include "SoundSystem.h"


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


	//SoundSystem* smgr = (SoundSystem*)(Engine::getEngine().System->getSystem("AUDIO"));
	//smgr->AddSound("C:/Assets/Sound/Sound.wav", "Bomb");

}

void MinesweeperState::Update(const float& dt) {
	//Engine::getEngine().pCam->UpdateMouseLook(dt);
}

void MinesweeperState::Render() {
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
	Engine::getShader().BindNewShader("DEFAULT2D");

	Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
	Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], Engine::get().default_cam->ProjectionMatrix, 1, false);
	Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], Engine::get().default_cam->ViewMatrix, 1, false);
	Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);
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

void MinesweeperState::KeyDown(int Key) {

}

void MinesweeperState::KeyUp(int Key) {
	//cLabelEntity* ent = (cLabelEntity*)(pEngine->EntityMgr->getEntity("testingTest"));
	//if (ent != nullptr) {
	//	ent->UpdateLabel("foo bar");
	//}

}

void MinesweeperState::MouseDown(int button) {

}

void MinesweeperState::MouseUp(int button) {

	switch (button)
	{
		case ENGINE_MOUSE_BUTTON_1:
		{
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

		} break;
	}

}

void MinesweeperState::MouseMove(float x, float y) {


	glm::vec3 pt = Engine::getRenderer().GetWorldPos2D((int)x, (int)y, Engine::get().default_cam->ProjectionMatrix, Engine::get().default_cam->ViewMatrix);

	mousex = (float)pt.x;
	mousey = (float)pt.y;

}

void MinesweeperState::RevealAll() {

	//SoundSystem* smgr = (SoundSystem*)(Engine::getEngine().System->getSystem("AUDIO"));
	//smgr->PlaySoundClip("Bomb");
	for (int x = 0; x < xsize; x++)
	{
		for (int y = 0; y < ysize; y++)
		{
			squares[x][y]->isRevealed = true;
		}
	}
}