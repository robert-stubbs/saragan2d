#ifndef _WORLD_H_
#define _WORLD_H_

#include "Types.h"
#include "Map.h"
#include "EntityManager.h"

namespace GameEngine
{

	class World
	{
		private:
			Map* current_map;
			std::map<std::string, Map*> _maps;
			EntityManager* _entity_mgr;

		public:
			World();
			~World();

			void LoadMap(std::string name, std::string map_path);
			void SetMap(std::string name);

			void Init();
			void Update(float dt);
			void RenderBackground();
			void Render();
			void RenderForeground();
			void RenderFade();


			void Cleanup();


			EntityManager* EntityMgr() { return _entity_mgr; }
	};

}

#endif