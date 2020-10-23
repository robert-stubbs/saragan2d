#ifndef _ENTITY_MANAGER_TOOL_H_
#define _ENTITY_MANAGER_TOOL_H_

#include "BaseTool.h"
#include "Entity.h"

namespace Editor {

	class EntityManagerTool : public BaseTool
	{
	private:


	public:
		EntityManagerTool() {};
		~EntityManagerTool() {};

		virtual void RenderUI() override;
		virtual void CreateEntityOption(GameEngine::Entity& ent);
	};
}

#endif