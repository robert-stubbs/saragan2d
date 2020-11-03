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

	void World::AddMap(std::string name, Map* m)
	{
		if (_maps.find(name) == _maps.end())
		{
			_maps[name] = m;
		}
	}

	void World::LoadMap(std::string name, std::string map_path, bool render_grid)
	{

		//std::map<std::string, Map> _maps;
		if (_maps.find(name) == _maps.end())
		{
			_maps[name] = new Map();
			_maps[name]->SetRenderGrid(true);
			_maps[name]->Init(name, map_path);
			_maps[name]->LoadMapFromFile(map_path, name);
		}
	}

	void World::SetMap(std::string name)
	{
		if (_maps.find(name) != _maps.end()) {

			// TODO need to render a fade here, once fade has completed
			//      then do the map processing

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

			// TODO hide fade overlay
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

	void World::RenderBackground()
	{
		Engine::getRenderer().EnableDepthTest(false);
		Engine::getRenderer().EnableBlend(true, GameEngine::BLEND_TYPE::SRC_ALPHA, GameEngine::BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

		if (current_map != nullptr)
		{
			current_map->RenderBackground();
		}

		Engine::getRenderer().EnableBlend(false);
		Engine::getRenderer().EnableDepthTest(true);
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

	void World::RenderForeground()
	{
		Engine::getRenderer().EnableDepthTest(false);
		Engine::getRenderer().EnableBlend(true, GameEngine::BLEND_TYPE::SRC_ALPHA, GameEngine::BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

		if (current_map != nullptr)
		{
			current_map->RenderForeground();
		}

		Engine::getRenderer().EnableBlend(false);
		Engine::getRenderer().EnableDepthTest(true);
	}

	void World::RenderFade()
	{

		// here is where we will be rendering the fade between levels

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