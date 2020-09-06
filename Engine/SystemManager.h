#ifndef _SYSTEM_MANAGER_H_
#define _SYSTEM_MANAGER_H_

namespace GameEngine
{
	class System;
	class Component;

	typedef std::shared_ptr<System> SharedSystemPtr;

	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager();

		bool AddSystem(System* system);
		System* getSystem(std::string Name);
		bool RemoveSystem(std::string Name);

		void AddComponentClass(std::string SystemName, Component* comp);

		void RemoveComponentsByHandle(std::string handle);

		void Init();
		void Update(float dt);
		void Render();
		void RenderAnim();
		void RenderUI();
		void CleanUp();


		static SystemManager* SysMgr;
		static inline SystemManager& getEngine() { return *SysMgr; }

	private:
		//map<string, cSystem> m_systems;
		std::map<std::string, SharedSystemPtr> sysBank;
	};
}

#endif