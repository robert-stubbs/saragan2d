#include "EditorPCH.h"
#include "ContextTool.h"

#include "GUI.h"

using namespace GameEngine;

namespace Editor {

	void ContextTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {
			GUI::Get().Begin("Main");

				ImGui::TextUnformatted("Main Area Test");

			GUI::Get().End();
		}
	}

}

