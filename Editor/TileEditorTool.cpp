#include "EditorPCH.h"
#include "TileEditorTool.h"

#include "GUI.h"
#include "Engine.h"

using namespace GameEngine;

namespace Editor {

	void TileEditorTool::LoadTexture(std::string path)
	{
		
		_t = Texture();
		_t.LoadFile(path, GameEngine::TEXTURETYPES::SARAGAN_PNG);
		_t.GenerateAlphaBuffer();
		_hasTexture = _t.loaded;

		tile_width = 32.0f;
		tile_height = 32.0f;
		number_of_tiles_width = _t.width / (int)tile_width;
		number_of_tiles_height = _t.height / (int)tile_height;

		delta_w = (float)tile_width / (float)_t.width;
		delta_h = (float)tile_height / (float)_t.height;

		selected_start_pos = start_pos;
		end_pos.x = delta_w * (float)(1);
		end_pos.y = delta_h * (float)(1);
		selected_end_pos.x = delta_w * (float)(1);
		selected_end_pos.y = delta_h * (float)(1);
		flags = ImGuiWindowFlags_HorizontalScrollbar;

	}

	void TileEditorTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			GUI::Get().Begin("Tile Editor");

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

			ImGui::BeginChild("Tile Map Settings", ImVec2(viewportPanelSize.x, 200), true, flags);

			ImGui::Image((ImTextureID)_t.TextureID, ImVec2(100, 100), selected_start_pos, selected_end_pos, bg_color, selected_tint_color);

			ImGui::EndChild();

			ImGui::BeginChild("colors", ImVec2(viewportPanelSize.x, viewportPanelSize.y - 200), true, flags);
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

					button_id  = 0;

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

							if (ImGui::ImageButton((ImTextureID)_t.TextureID, ImVec2(tile_width, tile_height), start_pos, end_pos, 1, bg_color, *temp)) {
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

			GUI::Get().End();
		}
	}

}

