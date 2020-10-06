#ifndef _CAMERA_SYSTEM_H_
#define _CAMERA_SYSTEM_H_

#include "System.h"

class Camera;

namespace GameEngine {

	class CameraSystem : public System
	{
	public:
		CameraSystem(bool isui = false, bool isanim = false);
		~CameraSystem();

		Camera* current_cam;

		virtual void Init();
		virtual void Update(float dt);
		virtual void Render() {};

		virtual void CleanUp();

		virtual void RemoveComponent(std::string handle);
		virtual Component* getComponent(std::string handle);

	};
}

#endif