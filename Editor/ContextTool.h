#ifndef _CONTEXT_TOOL_H_
#define _CONTEXT_TOOL_H_

#include "BaseTool.h"

namespace Editor {

	class ContextTool : public BaseTool
	{
	public:
		ContextTool() {};
		~ContextTool() {};

		virtual void RenderUI() override;

		virtual void MouseDown(int button) override;
		virtual void MouseUp(int button) override;

		virtual void MouseMove(float x, float y) override;
	};
}

#endif