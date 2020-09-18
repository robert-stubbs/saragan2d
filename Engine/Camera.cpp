#include "EnginePCH.h"
#include "Camera.h"
#include "SafeDelete.h"
#include "Entity.h"
#include "Location.h"


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
				// update view matrix
				cam->LookAt = loc->getPosition();
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