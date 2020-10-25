#include "EditorPCH.h"
#include "MainMenu.h"

#include "GUI.h"
#include "Engine.h"

using namespace GameEngine;

namespace Editor {

	void MainMenu::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New Map"))
					{
						NewMapModal = true;
					}
					else if (ImGui::MenuItem("Open Map")) {

						OpenMapModal = true;

					}
					else if (ImGui::MenuItem("Save Map")) {

						//Do something
						LOG("I CLICKED Save");

					}
					else if (ImGui::MenuItem("Save Map As")) {

						SaveAsMapModal = true;

					}
					else if (ImGui::MenuItem("Exit")) {
						PostQuitMessage(0);
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

				//################################################################################################
				// Menu Click Items
				//################################################################################################
				if (NewMapModal) {
					ImGui::OpenPopup("New Map");
				}

				if (OpenMapModal) {
					ImGui::OpenPopup("Open Map");
				}

				if (SaveAsMapModal) {
					ImGui::OpenPopup("SaveAs Map");
				}

				//################################################################################################
				// Modals
				//################################################################################################

				if (ImGui::BeginPopupModal("New Map"))
				{
					ImGui::Text("Lorem ipsum");

					if (ImGui::Button("Close")) {
						NewMapModal = false;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				if (ImGui::BeginPopupModal("Open Map"))
				{
					ImGui::Text("Lorem ipsum");
					World* w = Engine::getWorld();
					w->LoadMap("Test Level", "Maps/Test Level/");

					if (ImGui::Button("Close")) {

						w->SetMap("Test Level");
						OpenMapModal = false;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				if (ImGui::BeginPopupModal("SaveAs Map"))
				{
					ImGui::Text("Lorem ipsum");

					if (ImGui::Button("Close")) {
						SaveAsMapModal = false;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				//################################################################################################
			}

		}
	}

}

