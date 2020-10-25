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

			bool render_grid;
			bool grid_loaded;
			std::vector<vert2D> _grid_verts;
			unsigned int GridVAIO;
			unsigned int GridVBO;

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

			inline bool isLoaded() { return _loaded; }
			void unloadMap();

			void SetRenderGrid(bool render = false) { render_grid = render; }

			void Init(std::string name, std::string map_path);
			void ThreadLoad();
			bool LoadMapDefinition();
			void LoadTextureBuffers();
			void Update(float dt);
			
			void RenderBackground();
			void Render();
			void RenderForeground();

			void RenderLayer(int layer);

			void GenerateGrid();
			void RenderGrid();

			void Cleanup();

			virtual void LoadMapFromFile(std::string file_path, std::string name);

			virtual std::vector<std::string> split(std::string& str, std::string& delim);

			std::vector<Texture>* GetTextures() { return &_textures; }
			TileMap* GetDefinition() { return &_definition;  }
	};

}

#endif