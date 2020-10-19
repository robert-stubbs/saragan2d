#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "BaseTool.h"

namespace Editor {

	class MainMenu : public BaseTool
	{
	public:
		MainMenu() {};
		~MainMenu() {};

		virtual void RenderUI() override;
	};
}

#endif