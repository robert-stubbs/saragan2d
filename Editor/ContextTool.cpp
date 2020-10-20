#include "EditorPCH.h"
#include "ContextTool.h"

#include "GUI.h"

using namespace GameEngine;

namespace Editor {

	void ContextTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {
			GUI::Get().Begin("Main");

				ImVec2 pos = ImGui::GetCursorScreenPos();

				//ImGui::GetWindowDrawList()->AddImage(
				//	(void*)window.getRenderTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				//	ImVec2(ImGui::GetCursorScreenPos().x + window.getWidth() / 2, ImGui::GetCursorScreenPos().y + window.getHeight() / 2), ImVec2(0, 1), ImVec2(1, 0));



			GUI::Get().End();
		}
	}

}

