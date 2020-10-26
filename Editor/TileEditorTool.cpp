#include "EditorPCH.h"
#include "TileEditorTool.h"

#include "GUI.h"
#include "EditorDockTool.h"

using namespace GameEngine;

namespace Editor {

	void TileEditorTool::LoadTexture()
	{
		World* w = Engine::getWorld();
		Map* m = w->GetMap();

		if (m != nullptr) {
			def = m->GetDefinition();

			std::vector<Texture>* textures = m->GetTextures();

			if (textures->size()) {
				_t = &textures->at(0);

				_hasTexture = (_t->TextureID > 0);

				tile_width = (float)def->tile_width;
				tile_height = (float)def->tile_height;
				number_of_tiles_width = _t->width / (int)tile_width;
				number_of_tiles_height = _t->height / (int)tile_height;

				delta_w = (float)tile_width / (float)_t->width;
				delta_h = (float)tile_height / (float)_t->height;

				selected_start_pos = start_pos;
				end_pos.x = delta_w * (float)(1);
				end_pos.y = delta_h * (float)(1);
				selected_end_pos.x = delta_w * (float)(1);
				selected_end_pos.y = delta_h * (float)(1);
				flags = ImGuiWindowFlags_HorizontalScrollbar;
			}
		}
	}

	void TileEditorTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			ImGuiIO& io = ImGui::GetIO();
			auto f = io.Fonts->Fonts[5];

			GUI::Get().Begin("Tile Editor");		

			if (ImGui::IsWindowFocused() && _parent != nullptr) {
				((EditorDockTool*)_parent)->_current_tool = this;
				((EditorDockTool*)_parent)->has_current_tool = true;
			}

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

			ImGui::PushFont(f);

			ImGui::BeginChild("Tile Map Layers", ImVec2(viewportPanelSize.x, 200), true, flags);
				ImGui::Text("Layers:");

				ImGui::SameLine();
				if (ImGui::Button("Add")) {

				}
				ImGui::SameLine();
				if (ImGui::Button("Remove")) {

				}
				if (ImGui::ListBoxHeader("", ImVec2(viewportPanelSize.x - 20, 150)))
				{
					std::string layername = "";
					for (int i = 0; i < def->_layers.size(); i++)
					{
						layername = "Layer " + std::to_string(i);

						if (selected_layer == i) {
							layername += " - Selected";
						}
						ImGui::PushID((int)i);
						if (ImGui::Selectable(layername.c_str(), (selected_layer == i)))
						{
							// handle selection
							selected_layer = i;
						}
						ImGui::PopID();
					}

					ImGui::ListBoxFooter();
				}
				
			ImGui::EndChild();

			ImGui::PopFont();

			if (_t->TextureID) {

				ImGui::PushFont(f);

				ImGui::BeginChild("Tile Selection Details", ImVec2(viewportPanelSize.x-123, 120), true, flags);

				std::string loc = "Location: " + std::to_string((int)selected_x) + "," + std::to_string((int)selected_y);
				ImGui::Text(loc.c_str());

				ImGui::Text("Texture Min:");
				std::string min = "(" + std::to_string(selected_start_pos.x) + "," + std::to_string(selected_start_pos.y) + ")";
				ImGui::Text(min.c_str());

				ImGui::Text("Texture Max:");
				std::string max = "(" + std::to_string(selected_end_pos.x) + "," + std::to_string(selected_end_pos.y) + ")";
				ImGui::Text(max.c_str());

				ImGui::EndChild();

				ImGui::PopFont();
			
				ImGui::SameLine();

				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));
				ImGui::BeginChild("Tile Map Image", ImVec2(115, 120), true, flags);

				ImGui::Image((ImTextureID)_t->TextureID, ImVec2(100, 100), selected_start_pos, selected_end_pos, bg_color, selected_tint_color);

				ImGui::EndChild();
				ImGui::PopStyleVar();

				ImGui::BeginChild("colors", ImVec2(viewportPanelSize.x, viewportPanelSize.y - 330), true, flags);
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

				button_id = 0;

				for (int h = 0; h < number_of_tiles_height; h++)
				{
					ImGui::NewLine();
					for (int w = 0; w < number_of_tiles_width; w++)
					{
						ImGui::SameLine();

						start_pos.x = delta_w * (float)w;
						start_pos.y = delta_h * (float)h;
						end_pos.x = delta_w * (float)(w + 1);
						end_pos.y = delta_h * (float)(h + 1);

						ImVec4* temp = &bg_color;
						if (h == selected_y && w == selected_x) {
							temp = &selected_tint_color;
						}

						ImGui::PushID(button_id);

						if (ImGui::ImageButton((ImTextureID)_t->TextureID, ImVec2(tile_width, tile_height), start_pos, end_pos, 1, bg_color, *temp)) {
							selected_x = (float)w;
							selected_y = (float)h;
							selected_start_pos = start_pos;
							selected_end_pos = end_pos;
						}

						ImGui::PopID();
						button_id++;
					}
				}

				ImGui::PopStyleVar();
				ImGui::EndChild();
			}

			GUI::Get().End();
		}
	}

	void TileEditorTool::MouseDown(int button)
	{
		LOG("Mouse Down");
	}

	void TileEditorTool::MouseUp(int button)
	{
		LOG("Mouse Up");
	}

	void TileEditorTool::MouseMove(float x, float y)
	{
	}

	void TileEditorTool::MouseScroll(float xoffset, float yoffset)
	{
	}
}

