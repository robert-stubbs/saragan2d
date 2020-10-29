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

			ImGui::Text("ImGui Mouse X"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->gui_mouse_x);
			ImGui::Text("ImGui Mouse Y"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->gui_mouse_y);

			ImGui::Separator();

			ImGui::Text("System Mouse X"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->system_mouse_x);
			ImGui::Text("System Mouse Y"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->system_mouse_y);

			ImGui::Separator();

			ImGui::Text("ImGui Window X"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->window_x);
			ImGui::Text("ImGui Window Y"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->window_y);

			ImGui::Separator();

			ImGui::Text("Framebuffer Width"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->vp_width);
			ImGui::Text("Framebuffer Height"); ImGui::SameLine(); ImGui::InputFloat("", &_parent->vp_height);

			ImGui::Separator();

			ImGui::Text("Edit Viewport Focused"); ImGui::SameLine(); ImGui::Checkbox("", &Engine::get().EditorFocusViewport);

			GUI::Get().End();
		}
	}

}

