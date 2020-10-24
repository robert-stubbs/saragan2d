#ifndef _PROPERTIES_TOOL_H_
#define _PROPERTIES_TOOL_H_

#include "BaseTool.h"

namespace Editor {

	class PropertiesTool : public BaseTool
	{
	public:
		PropertiesTool() {};
		~PropertiesTool() {};

		virtual void RenderUI() override;
	};
}

#endif