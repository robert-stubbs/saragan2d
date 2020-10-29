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

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			ImGuiWindowClass window_class;
			window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoDocking;
			ImGui::SetNextWindowClass(&window_class)
				;
			GUI::Get().Begin("Main", true, window_flags);

				ImVec2 pos = ImGui::GetMousePos();
				
				_parent->gui_mouse_x = pos.x;
				_parent->gui_mouse_y = pos.y;

				ImVec2 window_pos =  ImGui::GetWindowPos();
				
				if (window_pos.x != _parent->window_x || window_pos.y != _parent->window_y) {
					_parent->window_x = window_pos.x;
					_parent->window_y = window_pos.y;
				}

				ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
				if (viewportPanelSize.x != _parent->vp_width || viewportPanelSize.y != _parent->vp_height) {
					_parent->vp_width = viewportPanelSize.x;
					_parent->vp_height = viewportPanelSize.y;

					Engine::getRenderer().ResizeFrameBuffer(Engine::get().FBO, Engine::get().FBOTexture, _parent->vp_width, _parent->vp_height);
					Engine::get().current_cam->resize(_parent->vp_width, _parent->vp_height);
				}

				ImGui::Image(reinterpret_cast<void*>(Engine::get().FBOTexture), ImVec2(_parent->vp_width, _parent->vp_height), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

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

			_parent->system_mouse_x = x;
			_parent->system_mouse_y = y;

			Engine& e = Engine::get();
			Camera2D* c = Engine::get().current_cam;

			glm::vec3 pt = Engine::getRenderer().GetWorldPos2D(
				(int)_parent->gui_mouse_x - _parent->window_x,
				(int)_parent->gui_mouse_y - _parent->window_y,
				Engine::get().current_cam->ProjectionMatrix, 
				Engine::get().current_cam->ViewMatrix,
				0,
				0,
				_parent->vp_width,
				_parent->vp_height
			);
			TileMap* d = m->GetDefinition();
			//m->UpdateHoverPosition(pt.x, pt.y);

			
				

			int x_quad = (int)pt.x / d->quad_width;
			int y_quad = (int)pt.y / d->quad_height;

			if (x_quad < d->map_width && y_quad < d->map_height) {

				m->UpdateHoverPosition(x_quad * d->quad_width, y_quad * d->quad_height);

			}
			
		}
	}

}

