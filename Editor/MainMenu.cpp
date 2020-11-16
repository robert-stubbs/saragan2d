#include "EditorPCH.h"
#include "MainMenu.h"

#include "GUI.h"
#include "Engine.h"

using namespace GameEngine;

namespace Editor {

	void MainMenu::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {
			World* w = Engine::getWorld();

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
			
					if (selected.length() > 0) {

						std::filesystem::path p = std::filesystem::path(selected);
						std::string file_name = p.stem().string();
						std::string folder = p.parent_path().string() + "\\";

						w->LoadMap(file_name, folder);
						w->SetMap(file_name);
					}
					OpenMapModal = false;
				}

				if (SaveAsMapModal) {
					std::string selected = Engine::getContext().Get().SaveFileDialog("Saragan Map (*.s_map)\0*.s_map\0");
		
					std::filesystem::path p = std::filesystem::path(selected);
					std::string file_name = p.stem().string();
					std::string folder = p.parent_path().string() + "\\";
					w->GetMap()->SaveMapAsToFile(folder, file_name);
					SaveAsMapModal = false;
				}

				//################################################################################################
				// Modals
				//################################################################################################
				ImGui::SetNextWindowPos(ImVec2(200, 100));
			
				if (ImGui::BeginPopupModal("New Map", &NewMapModal, 0))
				{
					ImGui::PushID("NewMapName");
					ImGui::Text("Map Name"); ImGui::SameLine(); ImGui::InputText("", &_new_map_name);
					ImGui::PopID();
					ImGui::PushID("NewMapWidth");
					ImGui::Text("Map Width"); ImGui::SameLine(); ImGui::InputInt("", &_new_map_width);
					ImGui::PopID();
					ImGui::PushID("NewMapHeight");
					ImGui::Text("Map Height"); ImGui::SameLine(); ImGui::InputInt("", &_new_map_height);
					ImGui::PopID();
					ImGui::PushID("NewMapDistance");
					ImGui::Text("Distance"); ImGui::SameLine(); ImGui::InputInt("", &_new_map_distance);
					ImGui::PopID();

					ImGui::Separator();
					if (ImGui::Button("Cancel")) {
						NewMapModal = false;
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button("Create")) {
						Map* m = new Map();
						m->NewMap(_new_map_name);
						m->SetMapDimension(50, _new_map_width, _new_map_height);
						m->SetRenderGrid(true);

						_map = m;

						w->AddMap(_new_map_name,_map);
						w->SetMap(_new_map_name);

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

