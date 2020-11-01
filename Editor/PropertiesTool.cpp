#include "EditorPCH.h"
#include "PropertiesTool.h"

#include "GUI.h"
#include "Engine.h"

using namespace GameEngine;

namespace Editor {

	void PropertiesTool::RenderUI()
	{
		if (GUI::GetGUI().HasInstance()) {

			GUI::Get().Begin("Properties");

			if (ImGui::IsWindowFocused() && _parent != nullptr) {
				has_focus = true;
			}
			else {
				has_focus = false;
			}

			if (_parent != nullptr && _parent->_current_tool != nullptr) {
				_parent->_current_tool->RenderProperties();
			}

			GUI::Get().End();
		}
	}

}

