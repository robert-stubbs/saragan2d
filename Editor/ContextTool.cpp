#include "EditorPCH.h"
#include "ContextTool.h"

#include "Engine.h"
#include "GUI.h"

using namespace GameEngine;

namespace Editor {

	void ContextTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {
			ImGui::SetNextWindowSize(ImVec2(Engine::get().RenderWidth / 2 + 10, Engine::get().RenderHeight / 2 + 10), ImGuiCond_FirstUseEver);

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			GUI::Get().Begin("Main");

				ImVec2 pos = ImGui::GetMousePos();
				
				gui_mouse_x = pos.x;
				gui_mouse_y = pos.y;

				ImVec2 window_pos =  ImGui::GetWindowPos();
				
				if (window_pos.x != window_x || window_pos.y != window_y) {
					window_x = window_pos.x;
					window_y = window_pos.y;
				}

				ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
				if (viewportPanelSize.x != vp_width || viewportPanelSize.y != vp_height) {
					vp_width = viewportPanelSize.x;
					vp_height = viewportPanelSize.y;

					Engine::getRenderer().ResizeFrameBuffer(Engine::get().FBO, Engine::get().FBOTexture, vp_width, vp_height);
					Engine::get().current_cam->resize(vp_width, vp_height);
				}

				ImGui::Image(reinterpret_cast<void*>(Engine::get().FBOTexture), ImVec2(vp_width, vp_height), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

				if (ImGui::IsWindowFocused()) {
					Engine::get().EditorFocusViewport = true;
				}
				else {
					Engine::get().EditorFocusViewport = false;
				}

			GUI::Get().End();

			ImGui::PopStyleVar();
		}
	}

	void ContextTool::MouseMove(float x, float y)
	{

		// This needs moved to the map when over the context window
		Map* m = Engine::getWorld()->GetMap();
		if (m != nullptr) {
			

				LOG("TEST Y" + std::to_string(gui_mouse_y) + " Y: " + std::to_string(y)  +" | WindowY: " + std::to_string(window_y));

				Engine& e = Engine::get();
				Camera2D* c = Engine::get().current_cam;

				glm::vec3 pt = Engine::getRenderer().GetWorldPos2D(
					(int)gui_mouse_x,
					(int)gui_mouse_y,
					Engine::get().current_cam->ProjectionMatrix, 
					Engine::get().current_cam->ViewMatrix,
					window_x,
					window_y,
					vp_width,
					vp_height
				);
				TileMap* d = m->GetDefinition();
				m->UpdateHoverPosition(pt.x, pt.y);

				/*
				

				int x_quad = (int)pt.x / d->map_width;
				int y_quad = (int)pt.y % d->map_height;

				if (x_quad < d->map_width && y_quad < d->map_height) {

					m->UpdateHoverPosition(x_quad * d->quad_width, y_quad * d->quad_height);

				}
				*/
			//}
		}
	}

}

