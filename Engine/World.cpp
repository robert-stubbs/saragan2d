#include "EnginePCH.h"
#include "World.h"
#include "Engine.h"

namespace GameEngine
{
	World::World()
	{
		_entity_mgr = new EntityManager();
		_maps = std::map<std::string, Map*>();
		current_map = nullptr;
	}

	World::~World()
	{

	}

	void World::LoadMap(std::string name, std::string map_path)
	{

		//std::map<std::string, Map> _maps;
		if (_maps.find(name) == _maps.end())
		{
			_maps[name] = new Map();
			_maps[name]->Init("Test Map", "");
		}
	}

	void World::SetMap(std::string name)
	{
		if (_maps.find(name) != _maps.end()) {
			// TODO set loading overlay

			// clear current_map
			if (current_map != nullptr) {
				current_map->unloadMap();
			}

			// set new current map
			current_map = _maps[name];

			//lazy load if not loaded
			if (!current_map->isLoaded())
			{
				_maps[name]->ThreadLoad();
			}
			// hide loading overlay
		}
	}

	void World::Init()
	{

	}

	void World::Update(float dt)
	{
		if (current_map != nullptr)
		{
			current_map->Update(dt);
		}
	}

	void World::Render()
	{
		Engine::getRenderer().EnableDepthTest(false);
		Engine::getRenderer().EnableBlend(true, GameEngine::BLEND_TYPE::SRC_ALPHA, GameEngine::BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

		if (current_map != nullptr)
		{
			current_map->Render();
		}

		Engine::getRenderer().EnableBlend(false);
		Engine::getRenderer().EnableDepthTest(true);
	}

	void World::Cleanup()
	{
		for (std::pair<std::string, Map*> pair : _maps) {
			SAFE_DELETE(pair.second);
		}

		current_map = nullptr;
		_maps.clear();
	}
}