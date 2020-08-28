#ifndef _TILE_H_
#define _TILE_H_

#include "GameLibrary.h"
#include "Square.h"

class Text;
class MinesweeperState;

using namespace GameEngine;

class Tile : public Square
{
public:
	Tile();
	~Tile();

	bool isBomb;
	int neighbourCount;
	bool isRevealed;
	//Text* text;

	std::vector<glm::vec2> direct_neighbours;

	virtual void ClickTile();

	virtual void Update(float dt);
	virtual bool Render();
	virtual void CleanUp();

	virtual void FindBombs(int x, int y, MinesweeperState* parent);
	virtual void ProcessNeighbours(int x, int y, MinesweeperState* parent);
	virtual void ProcessNeighbour(Tile* tile);
};

#endif

