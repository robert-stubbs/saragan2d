#include "EditorPCH.h"
#include "EntityManagerTool.h"

#include "GUI.h"
#include "Engine.h"
#include <imgui_internal.h>

using namespace GameEngine;

namespace Editor {


	void EntityManagerTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {
			// TODO Tool to manage Entities in World Map (empty until World Map is Loaded)
			GUI::Get().Begin("Entity Manager");

				ImGui::TextUnformatted("Entity Manager Area Test");

			GUI::Get().End();		
		}
	}

}

