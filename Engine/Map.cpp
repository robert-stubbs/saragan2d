#include "EnginePCH.h"
#include "Map.h"
#include "Engine.h"

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
		// as we dont have a resource manager we are loading the definition first by hand
		// then we will populate the class

		_definition.map_width = 1000;
		_definition.map_height = 1000;
		_definition.tile_width = 100;
		_definition.tile_height = 100;
		_definition.number_of_layers = 3;

		std::string path = Engine::get().asset_dir + "Textures/map_atlas.png";
		_definition._images.push_back({ 736, 928, path });

		for (TileAtlas atlas : _definition._images) {

		}


		Texture t = Texture();
		t.LoadFile(Engine::get().asset_dir + "Textures/testsprite.png", TEXTURETYPES::SARAGAN_PNG);
		

		_quads = std::vector <std::vector<std::vector<TextureQuad>>>();

		for (size_t i = 0; i < _definition.number_of_layers; i++)
		{
			for (int x = 0; x < _definition.map_width; x++)
			{
				for (int y = 0; y < _definition.map_height; y++)
				{



				}
			}
		}




		return true;
	}

	void Map::LoadTextureBuffers()
	{
		//if (t.LoadFile(Engine::get().asset_dir + "Textures/testsprite.png", TEXTURETYPES::SARAGAN_PNG))
		//{
		//	t.GenerateAlphaBuffer();
		//}

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