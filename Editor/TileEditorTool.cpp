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
	}

	void TileEditorTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			GUI::Get().Begin("Tile Editor");

			int tile_width = 32;
			int tile_height = 32;
			int number_of_tiles_width = _t.width / tile_width;
			int number_of_tiles_height = _t.height / tile_height;

			//
			ImGuiTreeNodeFlags flags = ImGuiWindowFlags_HorizontalScrollbar;

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			ImGui::BeginChild("colors", viewportPanelSize, true, flags);

			ImVec4 bg_color = ImVec4(255, 255, 255, 255);
			ImVec4 tint_color = ImVec4(0, 255, 0, 255);

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

			for (int w = 0; w < number_of_tiles_width; w++)
			{
				ImGui::NewLine();
				for (int h = 0; h < number_of_tiles_height; h++)
				{
					ImGui::SameLine();
					ImVec2 start_pos = ImVec2(0.0, 0.0);
					ImVec2 end_pos = ImVec2(1.0, 1.0);

					start_pos.x = ((float)tile_width / (float)_t.width) * (float)w;
					start_pos.y = ((float)tile_height / (float)_t.height) * (float)h;
					end_pos.x = ((float)tile_width / (float)_t.width) * (float)(w + 1);
					end_pos.y = ((float)tile_height / (float)_t.height) * (float)(h + 1);

					ImGui::ImageButton((void*)_t.TextureID, ImVec2(tile_width, tile_height), start_pos, end_pos, 1, bg_color);
				}
			}

			ImGui::PopStyleVar();
			ImGui::EndChild();

			GUI::Get().End();
		}
	}

}

