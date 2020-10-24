#include "EnginePCH.h"
#include "Map.h"
#include "Engine.h"
#include "standards.h"

namespace GameEngine
{
	Map::Map()
	{
		_batch = BatchRenderer("DEFAULT2D");
		distance_load = 10;
		min_x = 0;
		min_y = 0;
		max_x = 0;
		max_y = 0;
	}

	Map::~Map()
	{

	}

	void Map::unloadMap()
	{
		if (_loaded) {
			_loaded = false;
			_batch.UnloadBuffers();
			ZeroMemory(&_definition, sizeof(TileMap));
			_textures.clear();
			_quads.clear();
		}
	}

	void Map::Init(std::string name, std::string map_path)
	{
		_loaded = false;
		_name = name;
		_path = map_path;
	}

	void Map::ThreadLoad()
	{
		_loaded = false;
		_batch.Init(1000);
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

		TileLayer BGLayer = TileLayer();
		BGLayer.Tiles = std::vector<std::vector<SingleTile>>();
		for (int x = 0; x < _definition.map_width; x++)
		{
			BGLayer.Tiles.push_back(std::vector<SingleTile>());
			for (int y = 0; y < _definition.map_height; y++)
			{
				//23 x 29 - total for sheet
				BGLayer.Tiles[x].push_back({ 1, 2, 0 });

			}
		}
		_definition._layers.push_back(BGLayer);
		_definition.number_of_layers++;


		TileLayer main = TileLayer();
		main.Tiles = std::vector<std::vector<SingleTile>>();
		for (int x = 0; x < _definition.map_width; x++)
		{
			main.Tiles.push_back(std::vector<SingleTile>());
			for (int y = 0; y < _definition.map_height; y++)
			{
				//23 x 29 - total for sheet
				main.Tiles[x].push_back({ 1, 2, -1 });
			}
		}

		main.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		main.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		main.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		main.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		main.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		main.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };
		main.Tiles[GetRandomNumber(0, _definition.map_width - 1)][GetRandomNumber(0, _definition.map_height - 1)] = { 1, 7, 0 };

		_definition._layers.push_back(main);
		_definition.number_of_layers++;


		TileLayer FGLayer = TileLayer();
		FGLayer.Tiles = std::vector<std::vector<SingleTile>>();
		for (int x = 0; x < _definition.map_width; x++)
		{
			FGLayer.Tiles.push_back(std::vector<SingleTile>());
			for (int y = 0; y < _definition.map_height; y++)
			{				
				//23 x 29 - total for sheet
				FGLayer.Tiles[x].push_back({ 1, 2, -1 });
			}
		}

		_definition._layers.push_back(FGLayer);
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
		if (!_loaded) {
			return;
		}

		//any updates

		// for example when a player is moving you want to update
		// render a different part of the map


		glm::vec3 look = Engine::getRenderer().GetWorldPos2D((Engine::get().WindowWidth / 2), (Engine::get().WindowHeight / 2), Engine::get().current_cam->ProjectionMatrix, Engine::get().current_cam->ViewMatrix);

		int mod_x = (int)look.x % _definition.quad_width;
		int mod_y = (int)look.y % _definition.quad_height;

		int loc_x = (int)(look.x - mod_x) / _definition.quad_width;
		int loc_y = (int)(look.y - mod_y) / _definition.quad_height;

		loc_x = loc_x < 0 ? 0 : loc_x;
		loc_x = loc_x > _definition.map_width ? _definition.map_width : loc_x;

		loc_y = loc_y < 0 ? 0 : loc_y;
		loc_y = loc_y > _definition.map_height ? _definition.map_height : loc_y;

		min_x = loc_x - distance_load;
		max_x = loc_x + distance_load;

		min_y = loc_y - distance_load;
		max_y = loc_y + distance_load;

		min_y = min_y < 0 ? 0 : min_y;
		min_x = min_x < 0 ? 0 : min_x;

		max_x = max_x > _definition.map_height ? _definition.map_height : max_x;
		max_y = max_y > _definition.map_height ? _definition.map_height : max_y;
	}

	void Map::RenderBackground()
	{
		RenderLayer(0);
	}

	void Map::Render()
	{
		RenderLayer(1);
	}

	void Map::RenderForeground()
	{
		RenderLayer(2);
	}

	void Map::RenderLayer(int layer)
	{
		if (!_loaded) {
			return;
		}

		Engine::getShader().BindNewShader("DEFAULT2D");

		Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
		Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], Engine::get().current_cam->ProjectionMatrix, 1, false);
		Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], Engine::get().current_cam->ViewMatrix, 1, false);
		Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

		if (Engine::getRenderer().CurrentTextureID != _textures[0].TextureID)
		{
			if (!_textures[0].loaded) {
				LoadTextureBuffers();
			}
			Engine::getRenderer().CurrentTextureID = _textures[0].TextureID;
		}

		Engine::getRenderer().BindTextureBuffer(_textures[0].TextureID);

		if (layer < _definition.number_of_layers) {
			_batch.BeginBatch();
			for (int x = min_x; x < max_x; x++)
			{
				for (int y = min_y; y < max_y; y++)
				{
					_batch.AddQuad(_quads[layer][x][y]);
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