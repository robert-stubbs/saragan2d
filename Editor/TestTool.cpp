#include "EditorPCH.h"
#include "TestTool.h"

#include "GUI.h"
#include "Engine.h"

using namespace GameEngine;

namespace Editor {

	void TestTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New Map"))
					{
						//Do something
						LOG("I CLICKED NEW");
					} else if (ImGui::MenuItem("Open Map")) {

						//Do something
						LOG("I CLICKED Open");

					}
					else if (ImGui::MenuItem("Save Map")) {

						//Do something
						LOG("I CLICKED Save");

					}
					else if (ImGui::MenuItem("Save Map As")) {

						//Do something
						LOG("I CLICKED Save As");

					}
					ImGui::EndMenu();
				} 
				
				if (ImGui::BeginMenu("Sprites")) {

					if (ImGui::MenuItem("New Sprite"))
					{
						//Do something
						LOG("I CLICKED NEW Sprite");
					}
					ImGui::EndMenu();
				}

				ImGui::EndMainMenuBar();
			}

		}
	}

}

