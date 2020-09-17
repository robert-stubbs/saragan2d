#ifndef _CAMERA_2D_H_
#define _CAMERA_2D_H_

namespace GameEngine
{
	class Camera2D
	{
	public:

		bool toggleMouseLock;

		float speed;
		float mouseSpeed;

		float yaw;
		float pitch;

		float aspect;

		float dx; //how much we strafe on x
		float dy; //how much we walk on z
		float dz; //how much we walk on z

		glm::vec3 LookAt;

		glm::mat4 Pos;
		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;

		Camera2D();
		Camera2D(float width, float height);
		~Camera2D(void);

		POINT getMouseWindowPoint(HWND hWnd);

		void Update(float DeltaTime);
	};
}

#endif
