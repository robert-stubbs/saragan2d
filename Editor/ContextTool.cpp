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
			GUI::Get().Begin("Main");

				ImVec2 pos = ImGui::GetCursorScreenPos();
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
		}
	}

}

