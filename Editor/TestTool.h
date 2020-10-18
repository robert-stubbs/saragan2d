#ifndef _TEST_TOOL_H_
#define _TEST_TOOL_H_

#include "BaseTool.h"

namespace Editor {

	class TestTool : public BaseTool
	{
	public:
		TestTool() {};
		~TestTool() {};

		virtual void RenderUI() override;
	};
}

#endif