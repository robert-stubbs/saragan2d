#include "EditorPCH.h"
#include "TestTool.h"

#include "GUI.h"

using namespace GameEngine;

namespace Editor {

	void TestTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {
			GUI::Get().NewScene(1.0f / 60.0f);
			GUI::Get().DemoTest();
			GUI::Get().EndAndRender();
		}
	}

}

