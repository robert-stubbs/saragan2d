#include "EnginePCH.h"
#include "Camera2D.h"

namespace GameEngine
{
	Camera2D::Camera2D()
	{
		toggleMouseLock = false;

		speed = 0.20f;

		dx = 0;
		dz = 0;

		LookAt = glm::vec3(0.0f, 0.0f, 0.0f);

		aspect = (float)(800 / 600);
		ProjectionMatrix = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -10.0f, 10.0f);


		ViewMatrix = glm::mat4(1.0f);
		Pos = glm::mat4(1.0f);
	}

	Camera2D::Camera2D(float width, float height)
	{
		toggleMouseLock = false;

		speed = 0.20f;

		dx = 0;
		dz = 0;

		LookAt = glm::vec3(0.0f, 0.0f, 0.0f);

		aspect = (float)(width / height);
		ProjectionMatrix = glm::ortho(0.0f, width, height, 0.0f, -10.0f, 10.0f);


		ViewMatrix = glm::mat4(1.0f);
		Pos = glm::mat4(1.0f);
	}


	Camera2D::~Camera2D(void)
	{
	}

	void Camera2D::Update(float DeltaTime)
	{
		//get current view matrix
		glm::mat4 mat = ViewMatrix;

		LookAt.x += (dx) * speed;
		LookAt.y += (dy) * speed;

		glm::mat4 translate = glm::mat4(1.0f);
		translate = glm::translate(translate, -LookAt);

		ViewMatrix = translate;
	}

	POINT Camera2D::getMouseWindowPoint(HWND hWnd)
	{
		POINT point;
		GetCursorPos(&point);

		if (ScreenToClient(hWnd, &point)) {
			return point;
		}

		return POINT();
	}
}