#include "EditorPCH.h"
#include "MainMenu.h"

#include "GUI.h"
#include "Engine.h"
#include <filesystem>

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
						World* w = Engine::getWorld();
						Map* m = w->GetMap();
						if (m != nullptr) {
							m->SaveMapToFile();
						}

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
					std::string selected = Engine::getContext().Get().OpenFileDialog("Saragan Map (*.s_map)\0*.s_map\0");
		
					std::filesystem::path p = std::filesystem::path(selected);
					std::string file_name = p.stem().string();
					std::string folder = p.parent_path().string() + "\\";

					World* w = Engine::getWorld();
					w->LoadMap(file_name, folder);
					w->SetMap(file_name);
					OpenMapModal = false;
				}

				if (SaveAsMapModal) {
					std::string selected = Engine::getContext().Get().SaveFileDialog("Saragan Map (*.s_map)\0*.s_map\0");
		
					std::filesystem::path p = std::filesystem::path(selected);
					std::string file_name = p.stem().string();
					std::string folder = p.parent_path().string() + "\\";
					World* w = Engine::getWorld();
					w->GetMap()->SaveMapAsToFile(folder, file_name);
					SaveAsMapModal = false;
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
				//################################################################################################
			}

		}
	}

}

