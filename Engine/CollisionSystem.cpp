#include "EnginePCH.h"
#include "CollisionSystem.h"
#include "Collision.h"

#include "Component.h"
#include "Engine.h"

namespace GameEngine {

	CollisionSystem::CollisionSystem(bool isui, bool isanim) : System(isui, isanim)
	{
		SystemName = "COLLISION";
	}


	CollisionSystem::~CollisionSystem()
	{
	}

	void CollisionSystem::Init()
	{

	}


	void CollisionSystem::Update(float dt)
	{
		ComponentBank::iterator iter2;
		for (iter = m_components.begin(); iter != m_components.end(); iter++)
		{
			Collision* c1 = (Collision *)iter->get();
			c1->Update(dt);

			for (iter2 = m_components.begin(); iter2 != m_components.end(); iter2++)
			{
				if (iter != iter2) {
					Collision* c2 = (Collision*)iter2->get();
					if (c1->doesCollide(c2)) {

						if (c2->_loaded && c2->_render_collision) {
							c2->_has_collided = true;
							c2->UpdateSphereVerts();
						}

						c1->GetEntity()->hasCollided(c2);
						c2->GetEntity()->hasBeenCollided(c1);
					}
				}
			}
		}
	}
	
	void CollisionSystem::RenderUI()
	{
		Engine::getRenderer().EnableDepthTest(false);
		Engine::getRenderer().EnableBlend(true, BLEND_TYPE::SRC_ALPHA, BLEND_TYPE::ONE_MINUS_SRC_ALPHA);
		for (ComponentPtr ptr : m_components) {
			ptr->Render();
		}
		Engine::getRenderer().EnableBlend(false);
		Engine::getRenderer().EnableDepthTest(true);
	}

	void CollisionSystem::CleanUp()
	{

	}

	Component* CollisionSystem::getComponent(std::string handle)
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

	void CollisionSystem::RemoveComponent(std::string handle)
	{
		int count = (int)m_components.size();
		for (int i = 0; i < count; i++)
		{
			Collision* comp = (Collision*)m_components.at(i).get();
			if (comp->m_handle == handle)
			{
				m_components.erase(m_components.begin() + i);
				break;
				return;
			}
		}
	}


}