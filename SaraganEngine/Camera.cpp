#include "EnginePCH.h"
#include "Camera.h"

#include "Engine.h"

Camera::Camera(float width, float height)
{
	toggleMouseLock = false;

	speed = 0.75f;
	mouseSpeed = 0.005f;
	yaw = 360.0f;
	pitch = 0.0f;

	walkspeed = 0.5;
	strafespeed = 0.5;
	flyspeed = 0.5;

	dx = 0;
	dy = 0;
	dz = 0;

	//LookAt = glm::vec3(360.0f, 180.0f, 360.0f);
	LookAt = glm::vec3(0.0f, 0.0f, 0.0f);

	aspect = (float)(width / height);
	ProjectionMatrix = glm::perspective(45.0f, aspect, 0.1f, 2048.0f);

	ViewMatrix = glm::mat4(1.0f);
	Pos = glm::mat4(1.0f);

	matPitch = glm::mat4(1.0f);
	matYaw = glm::mat4(1.0f);
}


Camera::~Camera(void)
{
}

void Camera::Update(float DeltaTime)
{
	calcWalk();
	UpdateMouseLook(DeltaTime);

	UpdateViewMatrix();
}


void Camera::UpdateViewMatrix() {

	//roll can be removed from here. because is not actually used in FPS camera
	matPitch = glm::mat4(1.0f);//identity matrix
	matYaw = glm::mat4(1.0f);//identity matrix

	//roll, pitch and yaw are used to store our angles in our class
	matPitch = glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

	//order matters
	glm::mat4 rotate = matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -LookAt);

	ViewMatrix = rotate * translate;
}

void Camera::calcWalk() {

	//get current view matrix
	glm::mat4 mat = ViewMatrix;
	//row major
	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 up(mat[0][1], mat[1][1], mat[2][1]);
	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	LookAt += (-dz * forward + dy * up + dx * strafe) * speed;
}

void Camera::WalkForward()
{
	dz = walkspeed;
}

void Camera::WalkBack()
{
	dz = -walkspeed;
}

void Camera::FlyUp()
{
	dy = flyspeed;
}

void Camera::FlyDown()
{
	dy = -flyspeed;
}

void Camera::StrafeLeft()
{
	dx = -strafespeed;
}

void Camera::StrafeRight()
{
	dx = strafespeed;
}

void Camera::UpdateMouseLook(float deltaTime) {

	if (toggleMouseLock) {

		POINT p;
		GetCursorPos(&p);

		

		float diffx = (float)(p.x - (Engine::getEngine().width / 2));
		float diffy = (float)(p.y - (Engine::getEngine().height / 2));

		yaw += mouseSpeed * diffx;
		pitch += mouseSpeed * diffy;

		SetCursorPos((int)Engine::getEngine().width / 2, (int)Engine::getEngine().height / 2);

	}
}

void Camera::MouseDown() {

	toggleMouseLock = true;
	ShowCursor(false);
}

void Camera::MouseUp() {
	toggleMouseLock = false;
	ShowCursor(true);

}