#include "EnginePCH.h"
#include "Map.h"

namespace GameEngine
{
	Map::Map()
	{
		_batch = BatchRenderer("DEFAULT2D");
	}

	Map::~Map()
	{

	}

	void Map::Init(std::string name, std::string map_path)
	{
		_name = name;
		_path = map_path;
	}

	void Map::ThreadLoad()
	{
		_fut = std::async(std::launch::async, std::bind(&Map::LoadMapDefinition, this));
	}

	bool Map::LoadMapDefinition()
	{
		// load the quads/definition for the map
		// this could be threaded

		_definition.map_width = 1000;
		_definition.map_height = 1000;
		_definition.tile_width = 100;
		_definition.tile_height = 100;

		_quads = std::vector<std::vector<TextureQuad>>();


		return true;
	}

	void Map::Update()
	{
		//any updates

		// for example when a player is moving you want to update
		// render a different part of the map
	}

	void Map::Render()
	{
		// load quads into the batch renderer
	}

	void Map::Cleanup()
	{
		// any cleanup
	}
}