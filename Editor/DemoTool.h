#ifndef _DEMO_TOOL_H_
#define _DEMO_TOOL_H_

#include "BaseTool.h"

namespace Editor {

	class DemoTool : public BaseTool
	{
	public:
		DemoTool() {};
		~DemoTool() {};

		virtual void RenderUI() override;
	};
}

#endif