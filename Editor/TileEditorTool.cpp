#include "EditorPCH.h"
#include "TileEditorTool.h"

#include "GUI.h"
#include "EditorDockTool.h"

using namespace GameEngine;

namespace Editor {

	void TileEditorTool::LoadTexture()
	{
		if (current_image != selected_image) {
			World* w = Engine::getWorld();
			Map* m = w->GetMap();

			if (m != nullptr) {
				def = m->GetDefinition();

				std::vector<Texture>* textures = m->GetTextures();

				if (textures->size()) {
					_t = &textures->at(selected_image);

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
	}

	void TileEditorTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			ImGuiIO& io = ImGui::GetIO();
			auto f = io.Fonts->Fonts[5];

			GUI::Get().Begin("Tile Editor");		

			if (ImGui::IsWindowFocused() && _parent != nullptr) {
				has_focus = true;
				((EditorDockTool*)_parent)->_current_tool = this;
				((EditorDockTool*)_parent)->has_current_tool = true;
			}
			else {
				has_focus = false;
			}

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

			ImGui::PushFont(f);

			ImGui::BeginChild("Tile Map Layers", ImVec2(viewportPanelSize.x, 200), true, flags);
				ImGui::Text("Layers:");

				ImGui::SameLine();
				if (ImGui::Button("Add")) {
					Map* m = Engine::getWorld()->GetMap();
					selected_layer = m->AddLayer();
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove")) {
					Map* m = Engine::getWorld()->GetMap();
					m->RemoveLayer(selected_layer);
					selected_layer = 0;

				}
				ImGui::SameLine();
				if (ImGui::Button("Up")) {
					Map* m = Engine::getWorld()->GetMap();
					if (selected_layer > 0 && selected_layer < m->GetDefinition()->number_of_layers) {
						m->SwapLayer(selected_layer, selected_layer - 1);
						selected_layer--;
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Down")) {
					Map* m = Engine::getWorld()->GetMap();					
					if (selected_layer >= 0 && selected_layer < m->GetDefinition()->number_of_layers - 1) {
						m->SwapLayer(selected_layer, selected_layer + 1);
						selected_layer++;
					}
				}

				if (ImGui::ListBoxHeader("", ImVec2(viewportPanelSize.x - 20, 150)))
				{
					if (def->_layers.size() > 0) {
						std::string layername = "";
						for (int i = 0; i < def->_layers.size(); i++)
						{
							layername = def->_layers[i].name;

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
					}

					ImGui::ListBoxFooter();
				}
				
			ImGui::EndChild();

			ImGui::PopFont();

			if (_t != nullptr && _t->TextureID) {

				ImGui::BeginChild("colors", ImVec2(viewportPanelSize.x, viewportPanelSize.y - 210), true, flags);
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

	void TileEditorTool::RenderProperties() {

		ImGuiIO& io = ImGui::GetIO();
		auto f = io.Fonts->Fonts[5];
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		if (_t != nullptr && _t->TextureID) {
			ImGui::PushFont(f);

			ImGui::BeginChild("Tile Selection Details", ImVec2(viewportPanelSize.x - 123, 120), true, flags);

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
		}

		ImGui::Separator();

		if (def != nullptr && def->_layers.size() > 0)
		{
			TileLayer* l = &def->_layers[selected_layer];

			ImGui::PushID("Layer Name");
			ImGui::Text("Layer Name"); ImGui::SameLine(); ImGui::InputText("", &l->name);
			ImGui::PopID();

			std::string layer_index = "Layer Index: " + std::to_string(l->layer_index);
			ImGui::Text(layer_index.c_str());


			std::string layer_width = "Layer Width: " + std::to_string(l->width);
			std::string layer_height = "Layer Height: " + std::to_string(l->height);
			ImGui::Text(layer_width.c_str());
			ImGui::Text(layer_height.c_str());

			std::string tile_count = "Tile Count: " + std::to_string(l->width * l->height);
			ImGui::Text(tile_count.c_str());


			ImGui::PushFont(f);

			ImGui::BeginChild("Map Images", ImVec2(viewportPanelSize.x, 200), true, flags);
			ImGui::Text("Images:");

			ImGui::SameLine();
			if (ImGui::Button("Add")) {
				Map* m = Engine::getWorld()->GetMap();
				// TODO - from selection
				TileAtlas a = def->_images.at(0);
				def->_images.push_back(a);
				m->AddTexture(a);
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove")) {
				Map* m = Engine::getWorld()->GetMap();
				m->RemoveTexture(selected_image);
				if (m->GetDefinition()->_images.size() > 0)
				{
					selected_image = 0;
				}
			}

			if (ImGui::ListBoxHeader("", ImVec2(viewportPanelSize.x - 20, 150)))
			{
				std::string image_name = "";
				for (int i = 0; i < def->_images.size(); i++)
				{
					image_name = def->_images[i].name;

					ImGui::PushID(image_name.c_str());
					if (selected_image == i) {
						image_name += " - Selected";
					}
					if (ImGui::Selectable(image_name.c_str(), (selected_image == i)))
					{
						// handle selection
						selected_image = i;
						LoadTexture();											

						selected_x = 0;
						selected_y = 0;
						selected_start_pos = ImVec2(0.0, 0.0);
						selected_end_pos = ImVec2(0.0f + delta_w, 0.0f + delta_h);

					}
					ImGui::PopID();
				}

				ImGui::ListBoxFooter();
			}

			ImGui::EndChild();

			ImGui::PopFont();
		}
		//ImGui::Text("Edit Viewport Focused"); ImGui::SameLine(); ImGui::Checkbox("", &Engine::get().EditorFocusViewport);

		//ImGui::Separator();

		//ImGui::Text("World X"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->world_x);
		//ImGui::Text("World Y"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->world_y);


	
	}

	void TileEditorTool::MouseDown(int button)
	{
		if (button == 0) {
			LeftClickDown = true;
		}

		if (button == 1) {
			RightClickDown = true;
		}
	}

	void TileEditorTool::MouseUp(int button)
	{
		if (button == 0) {
			LeftClickDown = false;
			update_current_tile_x = true;
		}

		if (button == 1) {
			RightClickDown = false;
			update_current_tile_y = true;
		}
	}

	void TileEditorTool::MouseMoveContext(float x, float y)
	{
		_parent->system_mouse_x = x;
		_parent->system_mouse_y = y;

		Engine& e = Engine::get();
		Camera2D* c = Engine::get().current_cam;

		glm::vec3 pt = Engine::getRenderer().GetWorldPos2D(
			(int)_parent->gui_mouse_x - (int)_parent->window_x,
			(int)_parent->gui_mouse_y - (int)_parent->window_y,
			Engine::get().current_cam->ProjectionMatrix,
			Engine::get().current_cam->ViewMatrix,
			0,
			0,
			_parent->vp_width,
			_parent->vp_height
		);

		_parent->world_x = pt.x;
		_parent->world_y = pt.y;

		MouseMove(pt.x, pt.y);
	}

	void TileEditorTool::MouseMove(float x, float y)
	{
		// information for this should come from the Context Tool
		// (additional information is stored on the parent e.g. window_x of context etc
		Map* m = Engine::getWorld()->GetMap();
		TileMap* d = m->GetDefinition();

		if (d->number_of_layers > 0) {

			WorldSelectedX = (int)x / d->quad_width;
			WorldSelectedY = (int)y / d->quad_height;

			if (WorldSelectedX < d->map_width && WorldSelectedY < d->map_height) {
				m->UpdateHoverPosition((float)WorldSelectedX * d->quad_width, (float)WorldSelectedY * d->quad_height);
			}

			if (Engine::get().EditorFocusViewport && d->_images.size() > 0)
			{		
				int number_of_cols = (int)((float)d->_images.at(0).image_width / float(d->tile_width));
				int selected_tile = (selected_x) + ((selected_y) * number_of_cols);

				if (LeftClickDown && Input::Get().IsMouseButtonReleased(0)) {
					LeftClickDown = false;
				}
				if (RightClickDown && Input::Get().IsMouseButtonReleased(1)) {
					RightClickDown = false;
				}

				if (LeftClickDown || update_current_tile_x) {
					m->UpdateTileTexture(
						WorldSelectedX,
						WorldSelectedY,
						selected_layer,
						selected_tile,
						glm::vec2(selected_start_pos.x, selected_start_pos.y),
						glm::vec2(selected_end_pos.x, selected_end_pos.y)
					);
					update_current_tile_x = false;

				}
				else if (RightClickDown || update_current_tile_y) {
					m->UpdateTileTexture(
						WorldSelectedX,
						WorldSelectedY,
						selected_layer,
						0,
						glm::vec2(selected_start_pos.x, selected_start_pos.y),
						glm::vec2(selected_end_pos.x, selected_end_pos.y)
					);
					update_current_tile_y = false;
				}
			}
		}
	}

	void TileEditorTool::MouseScroll(float xoffset, float yoffset)
	{
	}
}

