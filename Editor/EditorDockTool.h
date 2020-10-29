#ifndef _EDITOR_DOCK_TOOL_H_
#define _EDITOR_DOCK_TOOL_H_

#include "BaseTool.h"
#include "EntityManagerTool.h"
#include "DebugTool.h"
#include "ResourcesTool.h"
#include "ContextTool.h"
#include "TileEditorTool.h"
#include "PropertiesTool.h"

namespace Editor {

	class EditorDockTool : public BaseTool
	{
	private:
		Editor::EntityManagerTool _entity_manager_panel;
		Editor::DebugTool _debug_window;
		Editor::ResourcesTool _resources_window;
		Editor::ContextTool _context_window;

		TileEditorTool _tile_editor_tool;
		PropertiesTool _properties_tool;

		ImGuiID left_dock_id;
		ImGuiID right_dock_id;
		ImGuiID bottom_dock_id;

		ImGuiID main_dock_id;

	public:

		EditorDockTool() {};
		~EditorDockTool() {};

		virtual void Init() override;
		virtual void RenderUI() override;

		virtual void MouseDown(int button) override;
		virtual void MouseUp(int button) override;
		virtual void MouseMove(float x, float y) override;
		virtual void MouseScroll(float xoffset, float yoffset) override;
	};
}

#endif