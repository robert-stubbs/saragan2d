#ifndef _TILE_EDITOR_TOOL_H_
#define _TILE_EDITOR_TOOL_H_

#include "BaseTool.h"
#include "Texture.h"
#include "Engine.h"
#include "World.h"
#include "Map.h"

namespace Editor {

	class TileEditorTool : public BaseTool
	{
	public:
		GameEngine::Texture* _t;
		std::string _path;
		bool _hasTexture = false;

		int selected_layer = 0;

		GameEngine::TileMap* def;

		ImGuiTreeNodeFlags flags;

		int button_id = 0;
		float tile_width;
		float tile_height;
		int number_of_tiles_width;
		int number_of_tiles_height;

		ImVec2 start_pos = ImVec2(0.0, 0.0);
		ImVec2 end_pos = ImVec2(1.0, 1.0);

		ImVec4 bg_color = ImVec4(255.0f, 255.0f, 255.0f, 255.0f);
		ImVec4 selected_tint_color = ImVec4(255.0f, 0.0f, 0.0f, 150.0f);

		float selected_x = 0;
		float selected_y = 0;
		ImVec2 selected_start_pos;
		ImVec2 selected_end_pos;

		float delta_w;
		float delta_h;

		TileEditorTool() {};
		~TileEditorTool() {};

		virtual void LoadTexture(std::string path);
		virtual void RenderUI() override;
	};
}

#endif