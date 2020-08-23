#include "GamePCH.h"
#include "RayState.h"

#include "Engine.h"
#include "Renderer.h"
#include "Line.h"
#include "Camera2D.h"


RayState::RayState() {
	stateName = "RayState";
	mousex = 0;
	mousey = 0;

	float width = (float)Engine::get().WindowWidth;
	float height = (float)Engine::get().WindowHeight;
		
	Line top = Line();
	top.Init(0.1f, 0.1f, width, 0.1f);
	hitLines.push_back(top);

	Line bottom = Line();
	bottom.Init(0.1f, height - 1, width, height - 1);
	hitLines.push_back(bottom);

	Line left = Line();
	left.Init(0.1f, 0.1f, 0.1f, height);
	hitLines.push_back(left);

	Line right = Line();
	right.Init(width, 0.1f, width, height);
	hitLines.push_back(right);

	for (size_t i = 0; i < 10; i++)
	{
		float x = (float)(rand() % ((int)width + 1) + 0);
		float y = (float)(rand() % ((int)height + 1) + 0);
		float x1 = (float)(rand() % ((int)width + 1) + 0);
		float y1 = (float)(rand() % ((int)height + 1) + 0);

		Line random = Line();
		random.Init(x, y, x1, y1);
		hitLines.push_back(random);
	}

	//for (size_t i = 0; i < 1; i += 1)
	//{
	//	Line current = Line();
	//	current.Init(mousex, mousey, (float)DEG2RAD(i));
	//	mouseLines.push_back(current);
	//}
	for (size_t i = 0; i < 360; i += 3)
	{
		Line current = Line();
		current.Init(mousex, mousey, (float)DEG2RAD(i));
		mouseLines.push_back(current);
	}
}

RayState::~RayState() {

}

void RayState::Init()
{

}

void RayState::Update(const float& dt) {
}

void RayState::Render() {

}

void RayState::UpdateOrth(const float& dt) {

	for (size_t i = 0; i < hitLines.size(); i++)
	{
		hitLines[i].Update(dt);
	}

	for (size_t i = 0; i < mouseLines.size(); i++)
	{
		mouseLines[i].Update(dt);
	}
}

void RayState::RenderOrth() {

	Engine::getShader().BindNewShader("DEFAULT2D");

	Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
	Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], Engine::get().cam->ProjectionMatrix, 1, false);
	Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], Engine::get().cam->ViewMatrix, 1, false);
	Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

	for (size_t i = 0; i < hitLines.size(); i++)
	{
		hitLines[i].Render();
	}

	for (size_t i = 0; i < mouseLines.size(); i++)
	{
		mouseLines[i].Render();
	}
}

void RayState::DoENTER() {

}

void RayState::DoEXIT() {

}

void RayState::KeyDown(int Key) {

}

void RayState::KeyUp(int Key) {

}

void RayState::MouseDown(int Button) {

}

void RayState::MouseUp(int Button) {

}

void RayState::MouseMove(float x, float y) {

	glm::vec3 pt = Engine::getRenderer().GetWorldPos2D((int)x, (int)y, Engine::get().cam->ProjectionMatrix, Engine::get().cam->ViewMatrix);

	mousex = (float)pt.x;
	mousey = (float)pt.y;


	for (size_t i = 0; i < mouseLines.size(); i++)
	{
		mouseLines[i].UpdatePos(mousex, mousey, hitLines);
		mouseLines[i].hasUpdate = true;
	}
}