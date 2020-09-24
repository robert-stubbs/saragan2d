#include "EnginePCH.h"
#include "Camera.h"
#include "SafeDelete.h"
#include "Entity.h"
#include "Location.h"
#include "Engine.h"
#include "Sprite.h"

namespace GameEngine {

	Camera::Camera() : Component()
	{
		m_type = "CAMERA";

	}

	Camera::~Camera()
	{
		CleanUp();
	}

	bool Camera::Init()
	{

		return true;
	}

	void Camera::Update(float dt)
	{
		if(e != nullptr && e->hasComponent("LOCATION")) {
			// get entity position from the position component
			Location* loc = (Location *)e->getComponent("LOCATION");
			if (loc != nullptr) {
				// set look at on camera to position x,y,z
				cam->LookAt = loc->getPosition();
				cam->LookAt.x -= (cam->res_width / 2);
				cam->LookAt.y -= (cam->res_height / 2);
			}

			Sprite* sp = (Sprite*)e->getComponent("SPRITE");
			if (sp != nullptr) {
				cam->LookAt.x += (sp->width / 2);
				cam->LookAt.y += (sp->height / 2);
			}
		}
		cam->Update(dt);
	}

	void Camera::Render()
	{

	}

	void Camera::CleanUp()
	{
		SAFE_DELETE(cam);
	}

	void Camera::SetUpCamera(float width, float height)
	{
		cam = new Camera2D(width, height);
	}
}