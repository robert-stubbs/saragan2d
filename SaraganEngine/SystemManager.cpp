#include "EnginePCH.h"
#include "SystemManager.h"

#include "System.h"
#include "Component.h"
#include "cErrorLogger.h"

SystemManager::SystemManager()
{
	sysBank.clear();

}

SystemManager::~SystemManager()
{


}


void SystemManager::Init()
{
	//SysMgr->AddSystem("position");
	//SysMgr->AddSystem("script");
	//SysMgr->AddSystem("input");
	//SysMgr->AddSystem("sound");
	//SysMgr->AddSystem("render");
	//SysMgr->AddSystem("collision");
	//SysMgr->AddSystem("camera");
	//SysMgr->AddSystem("sprite");
	//SysMgr->AddSystem("ai");


	//AddSystem(new cGUISystem(true));
	//AddSystem(new cSoundSystem());
	//AddSystem(new cAISystem());
	//AddSystem(new cModelSystem(false, true));
	//AddSystem(new cPositionSystem());
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
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
	{
		if (!(*iter).second->isAnim && !(*iter).second->isUI)
		{
			(*iter).second->Render();
		}
	}

	//glDisable(GL_BLEND);
}

void SystemManager::RenderAnim()
{
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
	{
		if ((*iter).second->isAnim && !(*iter).second->isUI)
		{
			(*iter).second->RenderAnim();
		}
	}

	//glDisable(GL_BLEND);
}

void SystemManager::RenderUI()
{
	//glDisable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	for (iter = sysBank.begin(); iter != sysBank.end(); iter++)
	{
		if (!(*iter).second->isAnim && (*iter).second->isUI)
		{
			(*iter).second->RenderUI();
		}
	}

	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
}


bool SystemManager::AddSystem(System* system)
{
	//add check to see if system already exists
	cErrorLogger::Log().WriteToConsole("> Add System: ");
	cErrorLogger::Log().WriteToConsole(system->SystemName);
	std::shared_ptr<System> newSystem(system);
	sysBank[system->SystemName] = newSystem;

	cErrorLogger::Log().WriteToConsole("..Done\n");
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

	//cEntity* Ent = pEngine->EntityMgr->getEntity(comp->m_handle);
	//if (Ent != nullptr)
	//{
	//	Ent->addComponent(comp);
	//}
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