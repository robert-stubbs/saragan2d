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
			

				LOG("TEST" + std::to_string(gui_mouse_y) + " Y: " + std::to_string(y)  +" | WindowY: " + std::to_string(window_y));

				// window X keeps moving window_x


		/*		

		return glm::unProject(glm::vec3((double)x, (double)winY, 0.0f), view, projection, glm::vec4(vpx, vpy, vpx2, vpy2));

				float new_x = vp_width * test_x;
				float new_y = vp_height * test_y;*/

				// we are in the editor window
				//glm::vec3 pt = Engine::getRenderer().GetWorldPos2D((int)new_x, (int)new_y, Engine::get().default_cam->ProjectionMatrix, Engine::get().default_cam->ViewMatrix);

				glm::vec3 pt = Engine::getRenderer().GetWorldPos2D(
								(int)gui_mouse_x,
								(int)gui_mouse_y,
								Engine::get().default_cam->ProjectionMatrix, 
								Engine::get().default_cam->ViewMatrix, 
								window_x,
								window_y,
								Engine::get().getRenderer().frame_buffer_width,
								Engine::get().getRenderer().frame_buffer_height
							);
				TileMap* d = m->GetDefinition();
				m->UpdateHoverPosition(pt.x, pt.y);
		/*		

								0,
								0,
								Engine::get().getRenderer().frame_buffer_width,
								Engine::get().getRenderer().frame_buffer_height
				

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

