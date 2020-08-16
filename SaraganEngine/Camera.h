#ifndef _CAMERA_H_
#define _CAMERA_H_


class Camera
{
public:

	POINT last_point;

	bool toggleMouseLock;

	float speed;
	float mouseSpeed;

	float yaw;
	float pitch;

	float aspect;

	float walkspeed;
	float strafespeed;
	float flyspeed;

	float dx; //how much we strafe on x
	float dy;
	float dz; //how much we walk on z

	glm::vec3 LookAt;

	glm::mat4 Pos;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

	glm::mat4 matPitch;
	glm::mat4 matYaw;

	Camera(float width, float height);
	~Camera(void);

	void Update(float DeltaTime);
	void UpdateViewMatrix();

	void calcWalk();

	void FlyUp();
	void FlyDown();
	void WalkForward();
	void WalkBack();
	void StrafeLeft();
	void StrafeRight();
	void UpdateMouseLook(float deltaTime);
	void MouseDown();
	void MouseUp();
};

#endif

