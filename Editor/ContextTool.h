#ifndef _CONTEXT_TOOL_H_
#define _CONTEXT_TOOL_H_

#include "BaseTool.h"

namespace Editor {

	class ContextTool : public BaseTool
	{
	public:
		ContextTool() {};
		~ContextTool() {};

		float window_x = 0.0f;
		float window_y = 0.0f;
		float vp_width = 0.0f;
		float vp_height = 0.0f;

		float gui_mouse_x = 0.0f;
		float gui_mouse_y = 0.0f;

		virtual void RenderUI() override;
		virtual void MouseMove(float x, float y) override;
	};
}

#endif