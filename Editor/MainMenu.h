#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "BaseTool.h"
#include "Map.h"

namespace Editor {

	class MainMenu : public BaseTool
	{
	public:
		MainMenu() {};
		~MainMenu() {};

		bool NewMapModal = false;
		bool OpenMapModal = false;
		bool SaveAsMapModal = false;
		
		GameEngine::Map* _map;

		std::string _new_map_name = "";
		int _new_map_width = 100;
		int _new_map_height = 100;
		int _new_map_distance = 50;

		virtual void RenderUI() override;
	};
}

#endif