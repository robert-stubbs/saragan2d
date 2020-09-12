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

			void Init(std::string name, std::string map_path);
			void ThreadLoad();
			bool LoadMapDefinition();
			void LoadTextureBuffers();
			void Update(float dt);
			void Render();
			void Cleanup();
	};

}

#endif