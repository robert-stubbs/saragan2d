#include "EnginePCH.h"
#include "Map.h"
#include "Engine.h"
#include "standards.h"
#include "FileManager.h"

#include "tinyxml2.h"

namespace GameEngine
{
	Map::Map()
	{
		_batch = BatchRenderer("DEFAULT2D");
		distance_load = 50;
		min_x = 0;
		min_y = 0;
		max_x = 0;
		max_y = 0;
		render_grid = false;
		grid_loaded = false;
		hover_loaded = false;
		GridVAIO = 0;
		GridVBO = 0;
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
		std::string asset_dir = Engine::get().asset_dir;

		for (TileAtlas atlas : _definition._images) {
			_textures.push_back(Texture());
			_textures.back().LoadFile(asset_dir + atlas.image_path + atlas.name, TEXTURETYPES::SARAGAN_PNG);		
		}	
		
		_quads = std::vector <std::vector<std::vector<TextureQuad>>>();

		int x_pos = 0;
		int y_pos = 0;

		glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		hover_color = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
		glm::vec2 min_text = { -99.0f,-99.0f };
		glm::vec2 max_text = { -99.0f,-99.0f };

		for (int i = 0; i < _definition.number_of_layers; i++)
		{
			_quads.push_back(std::vector<std::vector<TextureQuad>>());
			int texture_index = _definition._layers[i].sheet_id;
			float image_width = (float)_definition._images[texture_index].image_width;
			float image_height = (float)_definition._images[texture_index].image_height;
			float image_tile_width = (float)_definition._images[texture_index].tile_width;
			float image_tile_height = (float)_definition._images[texture_index].tile_height;
			int number_of_cols = (int)((float)image_width / float(image_tile_width));
			int number_of_rows = (int)((float)image_height / float(image_tile_height));

			for (int y = 0; y < _definition.map_height; y++)
			{
				_quads[i].push_back(std::vector<TextureQuad>());

				std::vector<SingleTile>& row = _definition._layers[i].Tiles[y];

				for (int x = 0; x < _definition.map_width; x++)
				{
					SingleTile& tile = row[x];

					color = glm::vec4(0.5f, 0.5f, 0.5f, 0.5f);
					min_text = { -99.0f,-99.0f };
					max_text = { -99.0f,-99.0f };

					if (texture_index > -1 && tile.tile_id > 0) {

						tile.tile_index_x = (tile.tile_id % number_of_cols);
						tile.tile_index_y = (tile.tile_id / number_of_rows);

						color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
						min_text.x = (image_tile_width / image_width) * (float)tile.tile_index_x;
						min_text.y = (image_tile_height / image_height) * (float)tile.tile_index_y;

						max_text.x = (image_tile_width / image_width) * (float)(tile.tile_index_x + 1);
						max_text.y = (image_tile_height / image_height) * (float)(tile.tile_index_y + 1);
					}

					_quads[i][y].push_back(TextureQuad());
					_quads[i][y][x].Init((float)x_pos, (float)y_pos, (float)_definition.quad_width, (float)_definition.quad_height, (float)i, min_text, max_text, color);

					x_pos += _definition.quad_width;

				}
				y_pos += _definition.quad_height;
				x_pos = 0;
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

	int Map::AddLayer()
	{
		TileLayer t = TileLayer();
		t.height = _definition.map_height;
		t.width = _definition.map_width;
		t.layer_index = (int)_definition._layers.size();
		_definition.number_of_layers++;

		t.name = "Layer " + std::to_string(t.layer_index);
		t.sheet_id = 0;
		t.Tiles = std::vector<std::vector<SingleTile>>();
		t.last_index = 0;

		for (int y = 0; y < _definition.map_height; y++)
		{
			t.Tiles.push_back(std::vector<SingleTile>());

			std::vector<SingleTile>& row = t.Tiles[y];

			for (int x = 0; x < _definition.map_width; x++)
			{
				SingleTile tile = SingleTile();
				tile.id = t.last_index;
				tile.tile_id = 0;
				tile.tile_index_x = x;
				tile.tile_index_y = y;

				row.push_back(tile);
				t.last_index++;
			}
		}

		_definition._layers.push_back(t);

		int x_pos = 0;
		int y_pos = 0;

		glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		hover_color = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
		glm::vec2 min_text = { -99.0f,-99.0f };
		glm::vec2 max_text = { -99.0f,-99.0f };

		int texture_index = _definition._layers[t.layer_index].sheet_id;

		TileAtlas& atlas = _definition._images[texture_index];

		float image_width = (float)atlas.image_width;
		float image_height = (float)atlas.image_height;
		float image_tile_width = (float)atlas.tile_width;
		float image_tile_height = (float)atlas.tile_height;
		int number_of_cols = (int)((float)image_width / float(image_tile_width));
		int number_of_rows = (int)((float)image_height / float(image_tile_height));

		float ratio_x = (image_tile_width / image_width);
		float ratio_y = (image_tile_height / image_height);

		_quads.push_back(std::vector<std::vector<TextureQuad>>());

		for (int y = 0; y < _definition.map_height; y++)
		{
			_quads[t.layer_index].push_back(std::vector<TextureQuad>());

			std::vector<SingleTile>& row = _definition._layers[t.layer_index].Tiles[y];

			for (int x = 0; x < _definition.map_width; x++)
			{
				SingleTile& tile = row[x];

				color = glm::vec4(0.5f, 0.5f, 0.5f, 0.5f);
				if (t.layer_index > 0) {
					color = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
				}
				min_text = { -99.0f,-99.0f };
				max_text = { -99.0f,-99.0f };

				if (texture_index > -1 && tile.tile_id > 0) {

					tile.tile_index_x = (tile.tile_id % number_of_cols);
					tile.tile_index_y = (tile.tile_id / number_of_rows);

					color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
					min_text.x = ratio_x * (float)tile.tile_index_x;
					min_text.y = ratio_y * (float)tile.tile_index_y;

					max_text.x = ratio_x * (float)(tile.tile_index_x + 1);
					max_text.y = ratio_y * (float)(tile.tile_index_y + 1);
				}

				_quads[t.layer_index][y].push_back(TextureQuad());
				_quads[t.layer_index][y][x].Init((float)x_pos, (float)y_pos, (float)_definition.quad_width, (float)_definition.quad_height, (float)t.layer_index, min_text, max_text, color);

				x_pos += _definition.quad_width;

			}
			y_pos += _definition.quad_height;
			x_pos = 0;
		}

		x_pos = 0;
		y_pos = 0;

		return t.layer_index;
	}

	void Map::RemoveLayer(int index)
	{

	}

	void Map::Update(float dt)
	{
		if (!_loaded) {
			return;
		}

		//any updates

		GenerateGrid();
		GenerateHoverQuad();

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
		RenderGrid();
		RenderHoverQuad();
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
			for (int y = min_y; y < max_y; y++)
			{
				for (int x = min_x; x < max_x; x++)
				{
					_batch.AddQuad(_quads[layer][y][x]);
				}
			}
			_batch.EndBatch();
		}
	}

	void Map::GenerateGrid()
	{
		if (!_loaded) {
			return;
		}

		if (render_grid && !grid_loaded && GridVAIO == 0) {

			_grid_verts = std::vector<vert2D>();

			float end_row = (float)(_definition.map_height * _definition.quad_height);
			float end_column = (float)(_definition.map_width * _definition.quad_width);
			glm::vec4 col = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);

			for (int y = 0; y < (int)_definition.map_height; y ++)
			{
				vert2D start = { {0,(float)_definition.quad_height*y,0.0f,1.0f},{-99.0f,-99.0f}, {col.r, col.g, col.b, col.a } };
				vert2D end = { {end_column,(float)_definition.quad_height*y,0.0f,1.0f},{-99.0f,-99.0f}, {col.r, col.g, col.b, col.a } };

				_grid_verts.push_back(start);
				_grid_verts.push_back(end);
			}

			for (int x = 0; x < (int)_definition.map_width; x ++)
			{
				vert2D start = { {(float)_definition.quad_width*x,0.0f,0.0f,1.0f},{-99.0f,-99.0f}, {col.r, col.g, col.b, col.a } };
				vert2D end = { {(float)_definition.quad_width * x,end_row,0.0f,1.0f},{-99.0f,-99.0f}, {col.r, col.g, col.b, col.a } };

				_grid_verts.push_back(start);
				_grid_verts.push_back(end);
			}

			Engine::getShader().BindNewShader("DEFAULT2D");
			Shader& s = Engine::getShader()["DEFAULT2D"];

			Engine::getRenderer().GenerateVertexArrayBuffer(GridVAIO);
			Engine::getRenderer().GenerateBuffer(GridVBO, _grid_verts);

			s.BindShaderStructure();

			Engine::getRenderer().UnbindBuffer();

			Engine::getRenderer().UnbindVertexBuffer();
		
			grid_loaded = true;
		}
	}

	void Map::RenderGrid()
	{
		if (render_grid && grid_loaded) {

			Engine::getShader().BindNewShader("DEFAULT2D");

			Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
			Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], Engine::get().current_cam->ProjectionMatrix, 1, false);
			Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], Engine::get().current_cam->ViewMatrix, 1, false);
			Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

			Engine::getRenderer().EnableBlend(true, BLEND_TYPE::SRC_ALPHA, BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

			Engine::getRenderer().BindVertexBuffer(GridVAIO);

			Engine::getRenderer().DrawArrays(DRAW_TYPE::LINES, (GLsizei)_grid_verts.size());

			Engine::getRenderer().UnbindVertexBuffer();

			Engine::getRenderer().EnableBlend(false);
		}
	}

	void Map::GenerateHoverQuad()
	{
		if (render_grid && !hover_loaded && HoverVAIO != 0) {

			vert2D tleft = { {0.0f,0.0f,-1.0f,1.0f},{-99.0f,-99.0f}, {hover_color.r, hover_color.g, hover_color.b, hover_color.a } };

			vert2D tright = { {(float)_definition.quad_width,0.0f,-1.0f,1.0f},{-99.0f,-99.0f}, {hover_color.r, hover_color.g, hover_color.b, hover_color.a } };

			vert2D bright = { {(float)_definition.quad_width,(float)_definition.quad_height,-1.0f,1.0f},{-99.0f,-99.0f}, {hover_color.r, hover_color.g, hover_color.b, hover_color.a } };

			vert2D bleft = { {0.0f,(float)_definition.quad_height,-1.0f,1.0f},{-99.0f,-99.0f}, {hover_color.r, hover_color.g, hover_color.b, hover_color.a } };

			_hover_verts.push_back(tleft);
			_hover_verts.push_back(tright);
			_hover_verts.push_back(bright);
			_hover_verts.push_back(bleft);

			Shader& s = Engine::getShader()["DEFAULT2D"];

			Engine::getRenderer().GenerateVertexArrayBuffer(HoverVAIO);
			Engine::getRenderer().GenerateBuffer(HoverVBO, _hover_verts);

			s.BindShaderStructure();

			Engine::getRenderer().UnbindBuffer();

			Engine::getRenderer().UnbindVertexBuffer();

			_hoverPos = glm::mat4(1.0f);
			hover_loaded = true;
		}
	}

	void Map::UpdateHoverPosition(float x, float y)
	{
		_hoverPos = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
	}

	void Map::RenderHoverQuad()
	{
		if (!_loaded) {
			return;
		}

		if (render_grid && hover_loaded) {

			Engine::getShader().BindNewShader("DEFAULT2D");
			Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], _hoverPos, 1, false);

			Engine::getRenderer().EnableBlend(true, BLEND_TYPE::SRC_ALPHA, BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

			Engine::getRenderer().BindVertexBuffer(HoverVAIO);

			Engine::getRenderer().DrawArrays(DRAW_TYPE::TRIANGLE_FAN, (GLsizei)_hover_verts.size());

			Engine::getRenderer().UnbindVertexBuffer();

			Engine::getRenderer().EnableBlend(false);

			Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);
		}
	}

	void Map::UpdateTileTexture(int x, int y, int layer, int texture_selection, glm::vec2 min, glm::vec2 max)
	{
		if (x >= 0 && y >= 0 && x < _definition.map_width && y < _definition.map_height) {
			SingleTile& t = _definition._layers[layer].Tiles[y][x];
			t.tile_id = texture_selection;
			t.tile_index_x = x;
			t.tile_index_y = y;

			TextureQuad& tile = _quads[layer][y][x];

			temp_color = glm::vec4(0.5f, 0.5f, 0.5f, 0.5f);
			if (layer > 0) {
				temp_color = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
			}

			if (texture_selection == 0) {
				tile.Init(tile.origin.x, tile.origin.y, tile.width, tile.height, tile.origin.z, glm::vec2(-99.0f, -99.0f), glm::vec2(-99.0f, -99.0f), temp_color);
			}
			else {
				tile.Init(tile.origin.x, tile.origin.y, tile.width, tile.height, tile.origin.z, min, max, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}

	void Map::Cleanup()
	{
		// any cleanup
	}
	
	void Map::LoadMapFromFile(std::string file_path, std::string name)
	{
		_loaded = false;
		_name = name;

		std::string map_path = Engine::get().asset_dir + file_path + name + ".s_map";

		_path = map_path;

		tinyxml2::XMLDocument doc;
		doc.LoadFile(map_path.c_str());
			
		int error = doc.ErrorID();

		tinyxml2::XMLElement* map = doc.FirstChildElement("map");

		_definition = TileMap();
		_definition._images = std::vector<TileAtlas>();

		// General settings
		_definition.version = (float)atof(map->Attribute("version"));
		_definition.map_width = atoi(map->Attribute("width"));
		_definition.map_height = atoi(map->Attribute("height"));
		_definition.tile_width = atoi(map->Attribute("tilewidth"));
		_definition.tile_height = atoi(map->Attribute("tileheight"));
		_definition.quad_width = atoi(map->Attribute("quad_width"));
		_definition.quad_height = atoi(map->Attribute("quad_height"));
		_definition.number_of_layers = 0;

		for (tinyxml2::XMLElement* e = map->FirstChildElement("sheets"); e != NULL; e = e->NextSiblingElement("sheets"))
		{
			tinyxml2::XMLElement* sheet = e->FirstChildElement("image");
			if (sheet != nullptr)
			{
				TileAtlas t = TileAtlas();
				t.id = atoi(sheet->Attribute("id"));
				t.name = sheet->Attribute("name");
				t.image_path = sheet->Attribute("path");
				t.type = sheet->Attribute("type");
				t.tile_width = atoi(sheet->Attribute("tilewidth"));
				t.tile_height = atoi(sheet->Attribute("tileheight"));
				t.image_width = atoi(sheet->Attribute("width"));
				t.image_height = atoi(sheet->Attribute("height"));
				_definition._images.push_back(t);
			}
		}

		for (tinyxml2::XMLElement* e = map->FirstChildElement("layer"); e != NULL; e = e->NextSiblingElement("layer"))
		{
			TileLayer l = TileLayer();
			l.layer_index = atoi(e->Attribute("id"));
			l.name = e->Attribute("name");
			l.width = atoi(e->Attribute("width"));
			l.height = atoi(e->Attribute("height"));
			l.sheet_id = atoi(e->Attribute("sheet_id"));

			l.last_index = 0;
			l.Tiles = std::vector<std::vector<GameEngine::SingleTile>>();

			// grab all the layer data
			std::string layer_data = e->FirstChildElement("data")->GetText();

			std::vector<std::string> vstrings = split(layer_data, std::string("\n"));

			for (std::string& s : vstrings)
			{
				std::vector<GameEngine::SingleTile> row = std::vector<GameEngine::SingleTile>();

				std::vector<std::string> row_strings = split(s, std::string(","));
					
				for (std::string& t : row_strings)
				{
					SingleTile tile = SingleTile();
					tile.id = l.last_index;
					tile.tile_id = atoi(t.c_str());

					row.push_back(tile);
					l.last_index++;
				}

				if (row.size() == l.width) {
					l.Tiles.push_back(row);
				}
			}

			_definition._layers.push_back(l);
			_definition.number_of_layers++;
		}		
	}

	std::vector<std::string> Map::split(std::string& str, std::string& delim)
	{
		std::vector<std::string> tokens;
		size_t prev = 0;
		size_t pos = 0;

		do
		{
			pos = str.find(delim, prev);
			if (pos == std::string::npos) { 
				pos = str.length(); 
			}

			std::string token = str.substr(prev, pos - prev);
			
			if (!token.empty()) {
				tokens.push_back(token);
			}

			prev = pos + delim.length();

		} while (pos < str.length() && prev < str.length());

		return tokens;
	}
}