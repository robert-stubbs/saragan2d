#include "EnginePCH.h"
#include "System.h"

#include "Component.h"
namespace GameEngine
{
	System::System(bool isui, bool isanim)
	{
		this->isUI = isui;
		this->isAnim = isanim;
	}

	void System::AddComponent(std::string handle)
	{
	}

	void System::AddComponentObject(Component* comp)
	{
		std::shared_ptr<Component> newSystem(comp);
		m_components.push_back(newSystem);
		//cEntity* ent = pEngine->EntityMgr->getEntity(comp->m_handle);
		//if (ent != nullptr)
		//{
		//	ent->m_components.push_back(newSystem);
		//}
	}
}