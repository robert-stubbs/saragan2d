#include "EditorPCH.h"
#include "DebugTool.h"

#include "GUI.h"
#include "Engine.h"

using namespace GameEngine;

namespace Editor {

	void DebugTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			// Show debug Log / allow editor Commands

			;
			if (!GUI::Get().Begin("Debug Window", &p_open))
			{
				GUI::Get().End();
				return;
			}

			// Set defined Window Size
			ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Close Console"))
					p_open = false;
				ImGui::EndPopup();
			}

			ImGui::TextWrapped(
				"This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys). A more elaborate "
				"implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
			ImGui::TextWrapped("Enter 'HELP' for help.");

			ImGui::Separator();

			// Options menu
			if (ImGui::BeginPopup("Options"))
			{
				//ImGui::Checkbox("Auto-scroll", &AutoScroll);
				ImGui::EndPopup();
			}

			// Options, Filter
			if (ImGui::Button("Options"))
				ImGui::OpenPopup("Options");
			ImGui::SameLine();
			//Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
			ImGui::Separator();

			// Reserve enough left-over height for 1 separator + 1 input text
			const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
			ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::Selectable("Clear")) {
					//ClearLog();
				}
				ImGui::EndPopup();
			}
			ImGui::EndChild();

			GUI::Get().End();
		}
	}

}

