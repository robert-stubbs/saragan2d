#include "EnginePCH.h"
#include "Triangle.h"

#include "Engine.h"

namespace GameEngine
{
	Triangle::Triangle() : Object()
	{

		shader_name = "DEFAULT2D";
	}

	Triangle::~Triangle()
	{

	}

	void Triangle::Init()
	{
		Shader& s = Engine::getShader().BindNewShader(shader_name);

		verts.push_back({ {-0.5f, -0.5f, 0.0f, 1.0f }, {-99.0f,-99.0f},  {1.0f, 0.0f, 0.0f, 1.0f } });
		verts.push_back({ { 0.0f,  0.5f, 0.0f, 1.0f }, {-99.0f,-99.0f},  {0.0f, 1.0f, 0.0f, 1.0f } });
		verts.push_back({ { 0.5f, -0.5f, 0.0f, 1.0f }, {-99.0f,-99.0f},  {0.0f, 0.0f, 1.0f, 1.0f } });


		Engine::getRenderer().GenerateBuffer(VBO, verts);

		Engine::getRenderer().VertexStructurePointerF(s["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
		Engine::getRenderer().VertexStructurePointerF(s["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
		Engine::getRenderer().VertexStructurePointerF(s["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

		Engine::getRenderer().UnbindVertexBuffer();

		isLoaded = true;

	}

	void Triangle::Update(float dt)
	{
		if (!isLoaded) return;

	}

	bool Triangle::Render()
	{
		if (!isLoaded) return false;

		//Engine::getShader().BindNewShader("DEFAULT2D");
		//Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
		//Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], glm::mat4(1.0f), 1, false);
		//Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], glm::mat4(1.0f), 1, false);
		//Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);

		Engine::getRenderer().EnableBlend(true, BLEND_TYPE::SRC_ALPHA, BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

		Engine::getRenderer().BindVertexBuffer(VBO);

		Engine::getRenderer().DrawArrays(DRAW_TYPE::TRIANGLES, (GLsizei)verts.size());

		Engine::getRenderer().UnbindVertexBuffer();

		Engine::getRenderer().EnableBlend(false);

		return true;
	}

	void Triangle::CleanUp()
	{

	}
}