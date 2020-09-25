#include "EnginePCH.h"
#include "World.h"
#include "Engine.h"

namespace GameEngine
{
	World::World()
	{
		_maps = std::map<std::string, Map*>();
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
			_maps[name]->ThreadLoad();
		}

		current_map = _maps[name];
	}

	void World::Init()
	{

	}

	void World::Update(float dt)
	{
		current_map->Update(dt);

	}

	void World::Render()
	{
		Engine::getRenderer().EnableDepthTest(false);
		Engine::getRenderer().EnableBlend(true, GameEngine::BLEND_TYPE::SRC_ALPHA, GameEngine::BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

		current_map->Render();

		Engine::getRenderer().EnableBlend(false);
		Engine::getRenderer().EnableDepthTest(true);
	}

	void World::Cleanup()
	{
		for (std::pair<std::string, Map*> pair : _maps) {
			SAFE_DELETE(pair.second);
		}

		current_map = nullptr;
		_maps.empty();
	}
}