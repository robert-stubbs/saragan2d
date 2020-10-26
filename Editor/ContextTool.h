#ifndef _CONTEXT_TOOL_H_
#define _CONTEXT_TOOL_H_

#include "BaseTool.h"

namespace Editor {

	class ContextTool : public BaseTool
	{
	public:
		ContextTool() {};
		~ContextTool() {};

		float vp_width = 0.0f;
		float vp_height = 0.0f;

		virtual void RenderUI() override;
	};
}

#endif