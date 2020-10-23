#include "EditorPCH.h"
#include "ResourcesTool.h"

#include "GUI.h"
#include "Engine.h"

using namespace GameEngine;

namespace Editor {

	void ResourcesTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			// TODO Tool to manage Assets Folder

			GUI::Get().Begin("Resources");

				ImGui::TextUnformatted("Resources Area Test");

				ImGui::Separator();

				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));

				if (ImGui::TreeNodeEx("Resources", flags)) {

					ImGui::Indent();
					ImGui::Text("Test");
					ImGui::Unindent();
					ImGui::TreePop();
				}
				ImGui::PopStyleVar();


			GUI::Get().End();
		}
	}

}

