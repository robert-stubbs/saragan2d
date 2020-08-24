#include "GamePCH.h"
#include "cTile.h"
#include "SafeDelete.h"

#include "MinesweeperState.h"
#include "Engine.h"
#include "Font.h"

Tile::Tile() {
	isBomb = false;
	neighbourCount = 0;
	isRevealed = false;
	//text = new Text();
}

Tile::~Tile() {

}

void Tile::ClickTile()
{
	colour = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	strokeColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	hasUpdate = true;
	isRevealed = true;
}

void Tile::Update(float dt)
{
	Square::Update(dt);

	//if (isRevealed && !text->loaded) {
	//	if (isBomb) {
	//		text->SetString(Engine::getEngine().font, "X", this->origin.x + 15, this->origin.y + 70, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//		text->Update(dt);
	//	}
	//	else {
	//		if (neighbourCount > 0) {
	//			std::string buffer = std::to_string(neighbourCount);
	//			text->SetString(Engine::getEngine().font, buffer, this->origin.x + 15, this->origin.y + 70, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	//			text->Update(dt);
	//		}
	//	}
	//}
}

bool Tile::Render()
{
	Square::Render();

	//if (isRevealed && text->loaded && (isBomb || neighbourCount > 0)) {
	//	glDisable(GL_DEPTH_TEST);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glEnable(GL_BLEND);
	//	text->Render();
	//	glDisable(GL_BLEND);
	//	glEnable(GL_DEPTH_TEST);
	//}

	return true;
}

void Tile::CleanUp()
{
	//SAFE_DELETE(text);
}

void Tile::FindBombs(int x, int y, MinesweeperState* parent)
{
	if (isBomb) {
		return;
	}

	direct_neighbours = std::vector<glm::vec2>();

	for (int x1 = -1; x1 <= 1; x1++)
	{
		for (int y1 = -1; y1 <= 1; y1++)
		{
			int curX = x + x1;
			int curY = y + y1;

			if (curX < 0 || curY < 0) {
				continue;
			}
			else if (curX == x && curY == y) {
				continue;
			}
			else if (curX >= xsize || curY >= ysize) {
				continue;
			}
			else {
				direct_neighbours.push_back(glm::vec2(curX, curY));
			}
		}
	}

	for (int n = 0; n < (int)direct_neighbours.size(); n++)
	{
		glm::vec2 next = direct_neighbours[n];

		Tile* t = parent->squares[(int)next.x][(int)next.y];
		if (t->isBomb) {
			this->neighbourCount++;
		}
	}
}

void Tile::ProcessNeighbours(int x, int y, MinesweeperState* parent)
{
	if (isBomb) {
		parent->RevealAll();
		return;
	}

	if (neighbourCount == 0) {

		ClickTile();

		for (int n = 0; n < (int)direct_neighbours.size(); n++)
		{
			glm::vec2 next = direct_neighbours[n];
			Tile* t = parent->squares[(int)next.x][(int)next.y];
			if (!t->isBomb && t->neighbourCount == 0 && !t->isRevealed) {
				t->ProcessNeighbours((int)next.x, (int)next.y, parent);
			}
			else if (!t->isBomb && t->neighbourCount > 0 && !t->isRevealed) {
				t->ProcessNeighbour(t);
			}
		}

	}
	else {
		colour = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
		strokeColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		hasUpdate = true;
		isRevealed = true;
	}
}

void Tile::ProcessNeighbour(Tile* tile)
{
	if (tile->isBomb || tile->isRevealed) {
		return;
	}
	else {
		tile->ClickTile();
	}
}