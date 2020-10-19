#ifndef _RESOURCES_TOOL_H_
#define _RESOURCES_TOOL_H_

#include "BaseTool.h"

namespace Editor {

	class ResourcesTool : public BaseTool
	{
	public:
		ResourcesTool() {};
		~ResourcesTool() {};

		virtual void RenderUI() override;
	};
}

#endif