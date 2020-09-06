#include "EnginePCH.h"
#include "SpriteSystem.h"
#include "Sprite.h"

#include "Component.h"

namespace GameEngine {

	SpriteSystem::SpriteSystem(bool isui, bool isanim) : System(isui, isanim)
	{
		SystemName = "SPRITE";
	}


	SpriteSystem::~SpriteSystem()
	{
	}

	void SpriteSystem::Init()
	{

	}


	void SpriteSystem::Update(float dt)
	{
		for (ComponentPtr ptr : m_components) {
			ptr->Update(dt);
		}
	}

	void SpriteSystem::RenderUI()
	{
		for (ComponentPtr ptr : m_components) {
			ptr->Render();
		}
	}

	void SpriteSystem::CleanUp()
	{

	}

	Component* SpriteSystem::getComponent(std::string handle)
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

	void SpriteSystem::RemoveComponent(std::string handle)
	{
		int count = (int)m_components.size();
		for (int i = 0; i < count; i++)
		{
			Sprite* comp = (Sprite*)m_components.at(i).get();
			if (comp->m_handle == handle)
			{
				m_components.erase(m_components.begin() + i);
				break;
				return;
			}
		}
	}


}