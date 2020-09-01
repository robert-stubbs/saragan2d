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

			std::vector<std::vector<TextureQuad>> _quads;

			std::future<bool> _fut;

		public:
			Map();
			~Map();

			void Init(std::string name, std::string map_path);
			void ThreadLoad();
			bool LoadMapDefinition();
			void Update();
			void Render();
			void Cleanup();
	};

}

#endif