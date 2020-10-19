#include "EditorPCH.h"
#include "EntityManagerTool.h"

#include "GUI.h"
#include "Engine.h"
#include <imgui_internal.h>

using namespace GameEngine;

namespace Editor {


	void EntityManagerTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			// TODO Tool to manage Entities in World Map (empty until World Map is Loaded)

			GUI::Get().Begin("Entity Manager");

			// Set defined Window Size
			ImGui::SetNextWindowSize(ImVec2(500, 100), ImGuiCond_FirstUseEver);


			GUI::Get().End();

			//static int initialized = 0;
			//static int new_window = 0;
			//ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
			//flags |= ImGuiWindowFlags_NoDocking;
			//ImGuiViewport* viewport = ImGui::GetMainViewport();
			//ImGui::SetNextWindowPos(viewport->Pos);
			//ImGui::SetNextWindowSize(viewport->Size);
			//ImGui::SetNextWindowViewport(viewport->ID);
			//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			//flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			//flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			//ImGui::Begin("DockSpace Demo", 0, flags);
			//ImGui::PopStyleVar();

			//if (ImGui::BeginMenuBar())
			//{
			//	if (initialized == 0)
			//	{
			//		if (ImGui::Button("1. Initialize"))
			//			initialized = 1;
			//	}
			//	if (initialized > 0 && new_window == 0)
			//	{
			//		if (ImGui::Button("2. New Window"))
			//			new_window = 1;
			//	}
			//	ImGui::EndMenuBar();
			//}

			//ImGuiIO& io = ImGui::GetIO();
			//ImGuiID dockspace_id = ImGui::GetID("MyDockspace");

			//if (initialized == 1)
			//{
			//	initialized = 2;
			//	ImGuiContext* ctx = ImGui::GetCurrentContext();				
			//	ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
			//	ImGui::DockBuilderAddNode(dockspace_id); // Add empty node				

			//	ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
			//	ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
			//	ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

			//	ImGui::DockBuilderDockWindow("Log", dock_id_bottom);
			//	ImGui::DockBuilderDockWindow("Properties", dock_id_prop);
			//	ImGui::DockBuilderFinish(dockspace_id);
			//}

			//ImGui::DockSpace(dockspace_id);
			//if (initialized == 2)
			//{
			//	ImGui::Begin("Properties");
			//	ImGui::End();

			//	ImGui::Begin("Log");
			//	ImGui::End();
			//}

			//if (new_window == 1)
			//{
			//	// Should dock window to empty space, instead window is not docked anywhere.
			//	ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_Once);
			//	ImGui::Begin("New Window");
			//	ImGui::End();
			//}

			//ImGui::End();
			//ImGui::PopStyleVar();
		}
	}

}

