#include "EnginePCH.h"
#include "SystemManager.h"

#include "Entity.h"
#include "Engine.h"
#include "EntityManager.h"

#include "System.h"
#include "Component.h"
//#include "cErrorLogger.h"

#include "ModelSystem.h"
#include "PositionSystem.h"
#include "AISystem.h"
#include "GUISystem.h"
#include "SoundSystem.h"

namespace GameEngine
{
	SystemManager* SystemManager::SysMgr = nullptr;

	SystemManager::SystemManager()
	{
		SysMgr = this;
		sysBank.clear();

	}

	SystemManager::~SystemManager()
	{


	}


	void SystemManager::Init()
	{
		//SysMgr->AddSystem("script");
		//SysMgr->AddSystem("input");
		//SysMgr->AddSystem("render");
		//SysMgr->AddSystem("collision");
		//SysMgr->AddSystem("camera");
		//SysMgr->AddSystem("sprite");


		AddSystem(new GUISystem(true));
		AddSystem(new SoundSystem());
		AddSystem(new AISystem());
		AddSystem(new ModelSystem(false, true));
		AddSystem(new PositionSystem());
	}

	void SystemManager::Update(float dt)
	{
		for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
		{
			(*iter).second->Update(dt);
		}

		//boost::thread positionSystem = boost::thread(&cPositionSystem::Update, (cPositionSystem*)SysMgr->getSystem("position"), dt);

		//positionSystem.join();
	}


	void SystemManager::Render()
	{

		for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
		{
			if (!(*iter).second->isAnim && !(*iter).second->isUI)
			{
				(*iter).second->Render();
			}
		}
	}

	void SystemManager::RenderAnim()
	{
		for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
		{
			if ((*iter).second->isAnim && !(*iter).second->isUI)
			{
				(*iter).second->RenderAnim();
			}
		}
	}

	void SystemManager::RenderUI()
	{
		for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
		{
			if (!(*iter).second->isAnim && (*iter).second->isUI)
			{
				(*iter).second->RenderUI();
			}
		}
	}


	bool SystemManager::AddSystem(System* system)
	{
		//add check to see if system already exists
		//cErrorLogger::Log().WriteToConsole("> Add System: ");
		//cErrorLogger::Log().WriteToConsole(system->SystemName);
		std::shared_ptr<System> newSystem(system);
		sysBank[system->SystemName] = newSystem;

		//cErrorLogger::Log().WriteToConsole("..Done\n");
		return true;
	}

	System* SystemManager::getSystem(std::string Name)
	{
		for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
		{
			if ((*iter).first == Name)
			{
				return iter->second.get();
			}
		}

		return nullptr;
	}

	bool SystemManager::RemoveSystem(std::string Name)
	{
		for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
		{
			if ((*iter).first == Name)
			{
				sysBank.erase(Name);
			}
		}

		return true;
	}

	void SystemManager::RemoveComponentsByHandle(std::string handle)
	{
		for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
		{
			std::string name = (*iter).first;
			sysBank[name]->RemoveComponent(handle);
		}
	}

	void SystemManager::AddComponentClass(std::string SystemName, Component* comp)
	{
		System* sys = getSystem(SystemName);

		sys->AddComponentObject(comp);

		Entity* Ent = Engine::getEngine().EntityMgr->getEntity(comp->m_handle);
		if (Ent != nullptr)
		{
			Ent->addComponent(comp);
		}
	}

	void SystemManager::CleanUp()
	{
		// call clean up on all systems
		for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
		{
			iter->second->CleanUp();
		}

		sysBank.clear();
	}
}