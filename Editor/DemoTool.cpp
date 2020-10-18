#include "EditorPCH.h"
#include "DemoTool.h"

#include "GUI.h"

using namespace GameEngine;

namespace Editor {

	void DemoTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {
			GUI::Get().NewScene(1.0f / 60.0f);
			GUI::Get().DemoTest();
			GUI::Get().EndAndRender();
		}
	}

}

