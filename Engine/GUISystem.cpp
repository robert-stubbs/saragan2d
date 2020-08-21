#include "EnginePCH.h"
#include "GUISystem.h"

#include "Engine.h"
#include "SafeDelete.h"
#include "Component.h"
#include "System.h"
#include "Font.h"

namespace GameEngine
{
	GUISystem::GUISystem(bool isui, bool isanim) : System(isui, isanim)
	{
		SystemName = "GUI";
		std::string asset_dir = "C:/Assets/";
		AddFontFile(20, asset_dir + "Font/Vera.ttf", "Main20");
	}

	GUISystem::~GUISystem()
	{


	}

	void GUISystem::Init()
	{
		// Add Default font
	}

	void GUISystem::Update(float dt)
	{
		for (ComponentBank::iterator it = m_components.begin(); it != m_components.end(); it++)
		{
			Component* c = it->get();
			c->Update(dt);
		}
	}

	void GUISystem::RenderUI()
	{
		for (ComponentBank::iterator it = m_components.begin(); it != m_components.end(); it++)
		{
			Component* c = it->get();
			if (c->renderLevel == 0) {
				c->Render();
			}
		}
		for (ComponentBank::iterator it = m_components.begin(); it != m_components.end(); it++)
		{
			Component* c = it->get();
			if (c->renderLevel == 1) {
				c->Render();
			}
		}
	}

	void GUISystem::CleanUp()
	{

	}

	void GUISystem::AddFontFile(float fontSize, std::string FontFile, std::string key)
	{
		Font* font = new Font(fontSize, FontFile);
		Fonts[key] = *font;
	}

	Font* GUISystem::getFont(std::string name)
	{
		Font* font = &Fonts[name];
		if (font != nullptr)
		{
			return font;
		}
		return nullptr;
	}

	void GUISystem::AddComponent(std::string handle)
	{
		Component* comp = getComponent(handle);

		if (comp == nullptr)
		{
			//Component* comp = new cLight();
			//comp->m_handle = handle;

			//std::tr1::shared_ptr<Component> newSystem(comp);
			//m_components.push_back(newSystem);
			//cEntity* ent = EtyMgr->getEntity(handle);
			//if (ent != nullptr)
			//{
			//	ent->m_components.push_back(newSystem);
			//}
		}

		return;
	}

	Component* GUISystem::getComponent(std::string handle)
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

	void GUISystem::RemoveComponent(std::string handle)
	{
		bool found = false;

		do
		{
			found = false;
			int count = (int)m_components.size();
			for (int i = 0; i < count; i++)
			{
				Component* comp = m_components.at(i).get();
				if (comp->m_handle == handle)
				{
					m_components.erase(m_components.begin() + i);
					found = true;
					break;
				}
			}

		} while (found);
	}
}
