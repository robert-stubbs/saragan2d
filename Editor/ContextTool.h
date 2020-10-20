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
	};
}

#endif