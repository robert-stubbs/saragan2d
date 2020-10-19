#ifndef _ENTITY_MANAGER_TOOL_H_
#define _ENTITY_MANAGER_TOOL_H_

#include "BaseTool.h"

namespace Editor {

	class EntityManagerTool : public BaseTool
	{
	private:

		char buf[255] = { 0 };
		float f = 0;

	public:
		EntityManagerTool() {};
		~EntityManagerTool() {};

		virtual void RenderUI() override;
	};
}

#endif