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

				ImGui::TextUnformatted("Resources Area Test");


			GUI::Get().End();
		}
	}

}

