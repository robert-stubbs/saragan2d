#include "EnginePCH.h"
#include "ModelSystem.h"
#include "Component.h"

ModelSystem::ModelSystem(bool isui, bool isanim) : System(isui, isanim)
{
	SystemName = "MODEL";
	m_components.clear();
}

ModelSystem::~ModelSystem()
{

}

void ModelSystem::Init()
{

}

void ModelSystem::Update(float dt)
{
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		Component* c = iter->get();
		c->Update(dt);
	}
}

void ModelSystem::Render()
{
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		Component* c = iter->get();
		if (!c->isAnim) {
			c->Render();
		}
	}
}

void ModelSystem::RenderAnim()
{
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		Component* c = iter->get();
		if (c->isAnim) {
			c->RenderAnim();
		}
	}
}

void ModelSystem::CleanUp()
{
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		(*iter)->CleanUp();
	}
}

void ModelSystem::RemoveComponent(std::string handle)
{
	int count = (int)m_components.size();
	for (int i = 0; i < count; i++)
	{
		//cMD5Item* comp = (cMD5Item*)m_components.at(i).get();
		//if (comp->m_handle == handle)
		//{
		//	m_components.erase(m_components.begin() + i);
		//	break;
		//	return;
		//}
	}
}

Component* ModelSystem::getComponent(std::string handle)
{
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		if ((*iter)->m_handle == handle)
		{
			return (*iter).get();
		}
	}

	return nullptr;
}