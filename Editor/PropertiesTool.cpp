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


			GUI::Get().End();
		}
	}

}

