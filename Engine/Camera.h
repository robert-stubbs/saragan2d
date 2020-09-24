#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Types.h"
#include "Component.h"
#include "Camera2D.h"

namespace GameEngine {

	class Camera : public Component {
	private:
		Camera2D* cam;

		glm::mat4 pos;

	public:
		Camera();
		virtual ~Camera();

		virtual bool Init() override;

		virtual void Update(float dt) override;

		virtual void Render() override;

		virtual void CleanUp() override;

		virtual void SetUpCamera(float width, float height);

		inline Camera2D* getCam2D() { return cam; }
	};

}

#endif