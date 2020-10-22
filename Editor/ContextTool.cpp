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

				ImGui::Image(reinterpret_cast<void*>(Engine::get().FBOTexture), ImVec2(viewportPanelSize.x, viewportPanelSize.y), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			GUI::Get().End();
		}
	}

}

