#ifndef _DEBUG_TOOL_H_
#define _DEBUG_TOOL_H_

#include "BaseTool.h"

namespace Editor {

	class DebugTool : public BaseTool
	{
	public:
		bool p_open;

		DebugTool() {};
		~DebugTool() {};

		virtual void RenderUI() override;
	};
}

#endif