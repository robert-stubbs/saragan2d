#ifndef _WORLD_H_
#define _WORLD_H_

#include "Types.h"
#include "Map.h"

namespace GameEngine
{

	class World
	{
		private:
			Map* current_map;
			std::map<std::string, Map*> _maps;

		public:
			World();
			~World();

			void LoadMap(std::string name, std::string map_path, bool set_map = false);
			void SetMap(std::string name);

			void Init();
			void Update(float dt);
			void Render();
			void Cleanup();


	};

}

#endif