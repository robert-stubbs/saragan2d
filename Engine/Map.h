#ifndef _MAP_H_
#define _MAP_H_

#include "Types.h"
#include "Texture.h"
#include "TextureQuad.h"
#include "BatchRenderer.h"

namespace GameEngine
{

	class Map
	{
		private:
			BatchRenderer _batch;
			std::string _name;
			std::string _path;
			TileMap _definition;

			glm::vec4 hover_color;
			glm::vec4 temp_color;

			bool render_grid;
			bool grid_loaded;
			std::vector<vert2D> _grid_verts;
			unsigned int GridVAIO;
			unsigned int GridVBO;

			bool hover_loaded;
			std::vector<vert2D> _hover_verts;
			unsigned int HoverVAIO;
			unsigned int HoverVBO;
			glm::mat4 _hoverPos;

			std::vector<Texture> _textures;

			std::vector<std::vector<std::vector<TextureQuad>>> _quads;

			std::future<bool> _fut;

			bool _loaded;

			int distance_load;

			int min_x;
			int min_y;
			int max_x;
			int max_y;

		public:
			Map();
			~Map();

			int current_x_hover;
			int current_y_hover;


			inline bool isLoaded() { return _loaded; }
			void unloadMap();

			void SetRenderGrid(bool render = false) { render_grid = render; }

			void Init(std::string name, std::string map_path);
			void ThreadLoad();
			bool LoadMapDefinition();
			void LoadTextureBuffers();
			
			void NewMap(std::string name);
			void SetMapDimension(int distance_to_load=50, int width=100, int height=100);

			int AddLayer();
			void RemoveLayer(int index);
			void SwapLayer(int from, int to);

			void AddTexture(TileAtlas a);
			
			void Update(float dt);
			
			void RenderBackground();
			void Render();
			void RenderForeground();

			void RenderLayer(int layer);

			void GenerateGrid();
			void RenderGrid();

			void GenerateHoverQuad();
			void UpdateHoverPosition(float x, float y);
			void RenderHoverQuad();

			void UpdateTileTexture(int x, int y, int layer, int texture_selection, glm::vec2 min, glm::vec2 max);

			void Cleanup();

			virtual void LoadMapFromFile(std::string file_path, std::string name);
			virtual void SaveMapToFile();
			virtual void SaveMapAsToFile(std::string file_path, std::string name);

			virtual std::vector<std::string> split(std::string& str, std::string& delim);

			std::vector<Texture>* GetTextures() { return &_textures; }
			TileMap* GetDefinition() { return &_definition;  }
	};

}

#endif