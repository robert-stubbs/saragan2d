#include "EditorPCH.h"
#include "EditorDockTool.h"

#include "GUI.h"
#include "Engine.h"
#include <imgui_internal.h>

using namespace GameEngine;

namespace Editor {

	void EditorDockTool::Init()
	{
		_entity_manager_panel = Editor::EntityManagerTool();

		_debug_window = Editor::DebugTool();
		_resources_window = Editor::ResourcesTool();

		_context_window = Editor::ContextTool();

		_tile_editor_tool = Editor::TileEditorTool();
		_tile_editor_tool.SetParent(this);

		_properties_tool = Editor::PropertiesTool();

		_current_tool = nullptr;
	}

	void EditorDockTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			static int initialized = 1;
			static int new_window = 0;
			ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
			flags |= ImGuiWindowFlags_NoDocking;
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace", 0, flags);
			ImGui::PopStyleVar();

			ImGuiIO& io = ImGui::GetIO();
			ImGuiID dockspace_id = ImGui::GetID("DockSpace");

			if (initialized == 1)
			{
				initialized = 2;
				ImGuiContext* ctx = ImGui::GetCurrentContext();
				ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
				ImGui::DockBuilderAddNode(dockspace_id); // Add empty node				

				ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.

				left_dock_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
				right_dock_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, NULL, &dock_main_id);
				bottom_dock_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

				main_dock_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.80f, NULL, &dock_main_id);

				ImGui::DockBuilderDockWindow("Debug Window", bottom_dock_id);
				
				ImGui::DockBuilderDockWindow("Main", main_dock_id);

				ImGui::DockBuilderDockWindow("Entity Manager", left_dock_id);

				ImGui::DockBuilderDockWindow("Resources", right_dock_id);
				ImGui::DockBuilderFinish(dockspace_id);
			}

			ImGui::DockSpace(dockspace_id);
			if (initialized == 2)
			{
				_entity_manager_panel.RenderUI();

				if (!_tile_editor_tool._hasTexture) {
					_tile_editor_tool.LoadTexture();
				}
				else {
					ImGui::SetNextWindowDockID(left_dock_id, ImGuiCond_Once);
					_tile_editor_tool.RenderUI();
				}

				ImGui::SetNextWindowDockID(bottom_dock_id, ImGuiCond_Once);
				_debug_window.RenderUI();

				ImGui::SetNextWindowDockID(main_dock_id, ImGuiCond_Once);
				_context_window.RenderUI();

				ImGui::SetNextWindowDockID(right_dock_id, ImGuiCond_Once);
				_resources_window.RenderUI();

				ImGui::SetNextWindowDockID(right_dock_id, ImGuiCond_Once);
				_properties_tool.RenderUI();
			}


	/*		ImGui::SetNextWindowDockID(main_dock_id, ImGuiCond_Once);
			ImGui::Begin("Main2");
			ImGui::End();*/

			ImGui::End();
			ImGui::PopStyleVar();
		}
	}

	void EditorDockTool::MouseDown(int button)
	{		
		if (_current_tool != nullptr && has_current_tool) {
			_current_tool->MouseDown(button);
		}
	}

	void EditorDockTool::MouseUp(int button)
	{
		if (_current_tool != nullptr && has_current_tool) {
			_current_tool->MouseUp(button);
		}
	}

	void EditorDockTool::MouseMove(float x, float y)
	{
		if (_current_tool != nullptr && has_current_tool) {
			_current_tool->MouseMove(x,y);
		}
	}

	void EditorDockTool::MouseScroll(float xoffset, float yoffset)
	{
		if (_current_tool != nullptr && has_current_tool) {
			_current_tool->MouseScroll(xoffset, yoffset);
		}
	}
}

