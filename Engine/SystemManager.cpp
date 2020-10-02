#include "EnginePCH.h"
#include "SystemManager.h"

#include "Entity.h"
#include "Engine.h"
//#include "EntityManager.h"

#include "System.h"
#include "Component.h"
//#include "cErrorLogger.h"

//#include "ModelSystem.h"
#include "PositionSystem.h"
#include "AISystem.h"
#include "SpriteSystem.h"
#include "SoundSystem.h"
#include "CameraSystem.h"
#include "CollisionSystem.h"

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

		//AddSystem(new GUISystem(true));
		AddSystem(new SoundSystem());
		AddSystem(new AISystem());
		AddSystem(new SpriteSystem(true));
		AddSystem(new CollisionSystem(true)); // only true for debug
		AddSystem(new PositionSystem());
		AddSystem(new CameraSystem());
	}

	void SystemManager::Update(float dt)
	{
		//for (std::pair<std::string, SharedSystemPtr> ptr: sysBank) {
		//	//ptr.second->Update(dt);
		//	std::future<void> _fut = std::async(std::launch::async, std::bind(&System::Update, ptr.second, dt));
		//}

		if (sysBank.find("SOUND") != sysBank.end()) {
			std::future<void> _fut_sound = std::async(std::launch::async, std::bind(&System::Update, sysBank["SOUND"], dt));
		}
		if (sysBank.find("AI") != sysBank.end()) {
			std::future<void> _fut_sound = std::async(std::launch::async, std::bind(&System::Update, sysBank["AI"], dt));
		}
		if (sysBank.find("LOCATION") != sysBank.end()) {
			std::future<void> _fut_sound = std::async(std::launch::async, std::bind(&System::Update, sysBank["LOCATION"], dt));
		}
		if (sysBank.find("CAMERA") != sysBank.end()) {
			std::future<void> _fut_sound = std::async(std::launch::async, std::bind(&System::Update, sysBank["CAMERA"], dt));
		}
		if (sysBank.find("SPRITE") != sysBank.end()) {
			std::future<void> _fut_sound = std::async(std::launch::async, std::bind(&System::Update, sysBank["SPRITE"], dt));
		}
		if (sysBank.find("COLLISION") != sysBank.end()) {
			std::future<void> _fut_sound = std::async(std::launch::async, std::bind(&System::Update, sysBank["COLLISION"], dt));
		}
	}


	void SystemManager::Render()
	{
		//for (std::pair<std::string, SharedSystemPtr> ptr : sysBank) {
		//	if (!ptr.second->isAnim && !ptr.second->isUI)
		//	{
		//		ptr.second->Render();
		//	}
		//}

		if (sysBank.find("AI") != sysBank.end()) {
			sysBank["AI"]->Render();
		}
	}

	void SystemManager::RenderAnim()
	{
		//for (std::pair<std::string, SharedSystemPtr> ptr : sysBank) {
		//	if (ptr.second->isAnim && !ptr.second->isUI)
		//	{
		//		ptr.second->RenderAnim();
		//	}
		//}
	}

	void SystemManager::RenderUI()
	{
		//for (std::pair<std::string, SharedSystemPtr> ptr : sysBank) {
		//	if (!ptr.second->isAnim && ptr.second->isUI)
		//	{
		//		ptr.second->RenderUI();
		//	}
		//}
		sysBank["SPRITE"]->RenderUI();
		sysBank["COLLISION"]->RenderUI();
	}


	bool SystemManager::AddSystem(System* system)
	{
		//add check to see if system already exists
		std::shared_ptr<System> newSystem(system);
		sysBank[system->SystemName] = newSystem;
		return true;
	}

	System* SystemManager::getSystem(std::string Name)
	{
		for (std::pair<std::string, SharedSystemPtr> ptr : sysBank) {
			if (ptr.first == Name)
			{
				return ptr.second.get();
			}
		}

		return nullptr;
	}

	bool SystemManager::RemoveSystem(std::string Name)
	{
		for (std::pair<std::string, SharedSystemPtr> ptr : sysBank) {
			if (ptr.first == Name)
			{
				sysBank.erase(Name);
			}
		}

		return true;
	}

	void SystemManager::RemoveComponentsByHandle(std::string handle)
	{
		for (std::pair<std::string, SharedSystemPtr> ptr : sysBank) {
			if (ptr.first == handle)
			{
				ptr.second->RemoveComponent(handle);
			}
		}
	}

	void SystemManager::AddComponentClass(std::string SystemName, Component* comp)
	{
		System* sys = getSystem(SystemName);

		sys->AddComponentObject(comp);
	}

	void SystemManager::CleanUp()
	{
		for (std::pair<std::string, SharedSystemPtr> ptr : sysBank) {
			ptr.second->CleanUp();
		}

		sysBank.clear();
	}
}