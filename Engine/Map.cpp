#include "EnginePCH.h"
#include "Map.h"
#include "Engine.h"
#include "standards.h"

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
		_loaded = false;
		_name = name;
		_path = map_path;
		_batch.Init(1000);
	}

	void Map::ThreadLoad()
	{
		_loaded = false;
		_fut = std::async(std::launch::async, std::bind(&Map::LoadMapDefinition, this));
	}

	bool Map::LoadMapDefinition()
	{
		// load the quads/definition for the map
		// as we dont have a resource manager we are loading the definition first by hand
		// then we will populate the class

		_definition.map_width = 20;
		_definition.map_height = 20;
		_definition.quad_width = 50;
		_definition.quad_height = 50;
		_definition.tile_width = 32;
		_definition.tile_height = 32;
		_definition.number_of_layers = 0;

		std::string path = Engine::get().asset_dir + "Textures/map_atlas.png";
		_definition._images.push_back({ 736, 928, path });

		TileLayer Layer0 = TileLayer();
		Layer0.Tiles = std::vector<std::vector<SingleTile>>();
		for (int x = 0; x < _definition.map_width; x++)
		{
			Layer0.Tiles.push_back(std::vector<SingleTile>());
			for (int y = 0; y < _definition.map_height; y++)
			{
				//23 x 29 - total for sheet
				Layer0.Tiles[x].push_back({ 1, 2, 0 });

			}
		}
		_definition._layers.push_back(Layer0);
		_definition.number_of_layers++;

		TileLayer Layer1 = TileLayer();
		Layer1.Tiles = std::vector<std::vector<SingleTile>>();
		for (int x = 0; x < _definition.map_width; x++)
		{
			Layer1.Tiles.push_back(std::vector<SingleTile>());
			for (int y = 0; y < _definition.map_height; y++)
			{				
				//23 x 29 - total for sheet
				Layer1.Tiles[x].push_back({ 1, 2, -1 });
			}
		}

		Layer1.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		Layer1.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		Layer1.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		Layer1.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		Layer1.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		Layer1.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		Layer1.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };


		_definition._layers.push_back(Layer1);
		_definition.number_of_layers++;


		for (TileAtlas atlas : _definition._images) {
			_textures.push_back(Texture());
			_textures.back().LoadFile(atlas.image_path, TEXTURETYPES::SARAGAN_PNG);
		}
			
		_quads = std::vector <std::vector<std::vector<TextureQuad>>>();

		int x_pos = 0;
		int y_pos = 0;
		for (int i = 0; i < _definition.number_of_layers; i++)
		{
			_quads.push_back(std::vector<std::vector<TextureQuad>>());

			for (int x = 0; x < _definition.map_width; x++)
			{
				_quads[i].push_back(std::vector<TextureQuad>());

				for (int y = 0; y < _definition.map_height; y++)
				{
					SingleTile& tile = _definition._layers[i].Tiles[x][y];
					int texture_index = tile.texture_index;

					glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
					glm::vec2 min_text = { -99.0f,-99.0f };
					glm::vec2 max_text = { -99.0f,-99.0f };

					if (texture_index > -1) {

						color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
						min_text.x = ((float)_definition.tile_width / (float)_definition._images[texture_index].image_width) * (float)tile.tile_index_x;
						min_text.y = ((float)_definition.tile_height / (float)_definition._images[texture_index].image_height) * (float)tile.tile_index_y;

						max_text.x = ((float)_definition.tile_width / (float)_definition._images[texture_index].image_width) * (float)(tile.tile_index_x + 1);
						max_text.y = ((float)_definition.tile_height / (float)_definition._images[texture_index].image_height) * (float)(tile.tile_index_y + 1);
					}

					_quads[i][x].push_back(TextureQuad());
					_quads[i][x][y].Init((float)x_pos, (float)y_pos, (float)_definition.quad_width, (float)_definition.quad_height, (float)i, min_text, max_text, color);

					y_pos += _definition.quad_height;
				}
				x_pos += _definition.quad_width;
				y_pos = 0;
			}
			x_pos = 0;
			y_pos = 0;
		}

		_loaded = true;

		return true;
	}

	void Map::LoadTextureBuffers()
	{
		for (Texture& t : _textures)
		{
			t.GenerateAlphaBuffer();
		}
	}

	void Map::Update(float dt)
	{


		//any updates

		// for example when a player is moving you want to update
		// render a different part of the map
	}

	void Map::Render()
	{
		if (!_loaded) {
			return;
		}

	    Engine::getShader().BindNewShader("DEFAULT2D");

	    Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
	    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], Engine::get().cam->ProjectionMatrix, 1, false);
	    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], Engine::get().cam->ViewMatrix, 1, false);
	    Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

		if (Engine::getRenderer().CurrentTextureID != _textures[0].TextureID)
		{
			if (!_textures[0].loaded) {
				LoadTextureBuffers();
			}
			Engine::getRenderer().CurrentTextureID = _textures[0].TextureID;

			Engine::getRenderer().BindTextureBuffer(_textures[0].TextureID);
		}

		//	
		for (int i = 0; i < _definition.number_of_layers; i++)
		{
			_batch.BeginBatch();
			for (int x = 0; x < _definition.map_width; x++)
			{
				for (int y = 0; y < _definition.map_height; y++)
				{
					_batch.AddQuad(_quads[i][x][y]);
				}
			}
			_batch.EndBatch();
		}

	}

	void Map::Cleanup()
	{
		// any cleanup
	}
}