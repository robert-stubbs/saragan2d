#include "EnginePCH.h"
#include "CameraSystem.h"
#include "Camera.h"

#include "Component.h"

namespace GameEngine {

	CameraSystem::CameraSystem(bool isui, bool isanim) : System(isui, isanim)
	{
		SystemName = "CAMERA";
	}


	CameraSystem::~CameraSystem()
	{
	}

	void CameraSystem::Init()
	{

	}


	void CameraSystem::Update(float dt)
	{
		for (ComponentPtr ptr : m_components) {
			ptr->Update(dt);
		}
	}

	void CameraSystem::CleanUp()
	{

	}

	Component* CameraSystem::getComponent(std::string handle)
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

	void CameraSystem::RemoveComponent(std::string handle)
	{
		int count = (int)m_components.size();
		for (int i = 0; i < count; i++)
		{
			Camera* comp = (Camera*)m_components.at(i).get();
			if (comp->m_handle == handle)
			{
				m_components.erase(m_components.begin() + i);
				break;
				return;
			}
		}
	}
}