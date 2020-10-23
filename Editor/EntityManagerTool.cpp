#include "EditorPCH.h"
#include "EntityManagerTool.h"

#include "GUI.h"
#include "Engine.h"
#include "EntityManager.h"
#include <imgui_internal.h>

using namespace GameEngine;

namespace Editor {


	void EntityManagerTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {
			// TODO Tool to manage Entities in World Map (empty until World Map is Loaded)
			GUI::Get().Begin("Entity Manager");

				ImGui::TextUnformatted("Entity Manager Area Test");

				ImGui::Separator();

				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));

				if (ImGui::TreeNodeEx("Entities", flags)) {

					ImGui::Indent();
					
					
					// loop over the entities
					for (GameEngine::EntityPtr ent : Engine::EntityMgr()->m_entities) {

						CreateEntityOption(*ent.get());

					}
					
					
					ImGui::Unindent();
					ImGui::TreePop();
				}
				ImGui::PopStyleVar();


			GUI::Get().End();		
		}
	}

	void EntityManagerTool::CreateEntityOption(GameEngine::Entity& ent)
	{

		ImGui::Text(ent.m_handle.c_str());
	}

}

