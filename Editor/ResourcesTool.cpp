#include "EditorPCH.h"
#include "ResourcesTool.h"

#include "GUI.h"
#include "Engine.h"

using namespace GameEngine;

namespace Editor {

	void ResourcesTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			// TODO Tool to manage Assets Folder

			GUI::Get().Begin("Resources");

			// Set defined Window Size
			ImGui::SetNextWindowSize(ImVec2(500, 100), ImGuiCond_FirstUseEver);


			GUI::Get().End();
		}
	}

}

