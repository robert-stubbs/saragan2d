#include "EnginePCH.h"
#include "Camera2D.h"

namespace GameEngine
{
	Camera2D::Camera2D()
	{
		toggleMouseLock = false;

		zoom_level = 1.0f;

		speed = 0.20f;

		dx = 0;
		dz = 0;

		LookAt = glm::vec3(0.0f, 0.0f, 0.0f);

		resize(800.0f, 600.0f);

		ViewMatrix = glm::mat4(1.0f);
		Pos = glm::mat4(1.0f);
	}

	Camera2D::Camera2D(float width, float height)
	{
		toggleMouseLock = false;

		zoom_level = 1.0f;

		speed = 0.20f;

		dx = 0;
		dz = 0;

		LookAt = glm::vec3(0.0f, 0.0f, 0.0f);

		resize(width, height);

		ViewMatrix = glm::mat4(1.0f);
		Pos = glm::mat4(1.0f);
	}

	void Camera2D::resize(float width, float height)
	{
		res_width = width;
		res_height = height;
		aspect = (float)(width / height);
		ProjectionMatrix = glm::ortho(0.0f*zoom_level, width * zoom_level, height * zoom_level, 0.0f * zoom_level, -10.0f, 10.0f);
	}

	Camera2D::~Camera2D(void)
	{
	}

	void Camera2D::Update(float DeltaTime)
	{
		LookAt.x += (dx) * speed * zoom_level;
		LookAt.y += (dy) * speed * zoom_level;

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

	void Camera2D::AdjustZoom(float val)
	{
		zoom_level -= val;

		if (zoom_level < 1.0f)
		{
			zoom_level = 1.0f;
		}

		ProjectionMatrix = glm::ortho(0.0f * zoom_level, res_width * zoom_level, res_height * zoom_level, 0.0f * zoom_level, -10.0f, 10.0f);
	}
}