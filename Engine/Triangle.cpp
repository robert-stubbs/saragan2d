#include "EnginePCH.h"
#include "Triangle.h"

#include "Engine.h"

namespace GameEngine
{
	Triangle::Triangle() : Object()
	{
		rotator = glm::mat4(1.0f);
		origin = glm::vec3(1.0f);
		shader_name = "DEFAULT2D";
	}

	Triangle::~Triangle()
	{
		//Engine::getRenderer().DeleteBuffer(VBO);
		//Engine::getRenderer().DeleteVertexBuffer(VAIO);
	}

	void Triangle::Init()
	{
		this->center = glm::vec3((-0.5f + 0.5f) / 3, (-0.5f + 0.5f + -0.5f) / 3, 0.0f);

		this->origin = glm::vec3(0.0f, 0.0f, 0.0f);
		rotator = glm::translate(glm::mat4(1.0f), origin);

		Shader& s = Engine::getShader().BindNewShader(shader_name);

		verts.push_back({ {-0.5f, -0.5f, 0.0f, 1.0f }, {-99.0f,-99.0f},  {1.0f, 0.0f, 0.0f, 1.0f } });
		verts.push_back({ { 0.0f,  0.5f, 0.0f, 1.0f }, {-99.0f,-99.0f},  {0.0f, 1.0f, 0.0f, 1.0f } });
		verts.push_back({ { 0.5f, -0.5f, 0.0f, 1.0f }, {-99.0f,-99.0f},  {0.0f, 0.0f, 1.0f, 1.0f } });

		Engine::getRenderer().GenerateVertexArrayBuffer(VAIO);

		Engine::getRenderer().GenerateBuffer(VBO, verts);

		Engine::getRenderer().VertexStructurePointerF(s["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
		Engine::getRenderer().VertexStructurePointerF(s["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
		Engine::getRenderer().VertexStructurePointerF(s["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

		Engine::getRenderer().UnbindBuffer();
		Engine::getRenderer().UnbindVertexBuffer();

		isLoaded = true;

	}
		
	void Triangle::Init(float x1, float y1, float x2, float y2, float x3, float y3)
	{
		Shader& s = Engine::getShader().BindNewShader(shader_name);

		this->center = glm::vec3((x1+x2+x3)/3, (y1 + y2 + y3) / 3, 0.0f);

		this->origin = glm::vec3(400.0f, 300.0f, 0.0f);
		rotator = glm::translate(glm::mat4(1.0f), origin);
		

		verts.push_back({ { x1, y1, 0.0f, 1.0f }, {-99.0f,-99.0f},  {1.0f, 0.0f, 0.0f, 1.0f } });
		verts.push_back({ { x2, y2, 0.0f, 1.0f }, {-99.0f,-99.0f},  {0.0f, 1.0f, 0.0f, 1.0f } });
		verts.push_back({ { x3, y3, 0.0f, 1.0f }, {-99.0f,-99.0f},  {0.0f, 0.0f, 1.0f, 1.0f } });

		Engine::getRenderer().GenerateVertexArrayBuffer(VAIO);

		Engine::getRenderer().GenerateBuffer(VBO, verts);

		Engine::getRenderer().VertexStructurePointerF(s["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
		Engine::getRenderer().VertexStructurePointerF(s["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
		Engine::getRenderer().VertexStructurePointerF(s["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

		Engine::getRenderer().UnbindBuffer();

		Engine::getRenderer().UnbindVertexBuffer();

		isLoaded = true;

	}

	void Triangle::Update(float dt)
	{
		if (!isLoaded) return;

		rotator = glm::translate(rotator, center);
		rotator = glm::rotate(rotator, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		rotator = glm::translate(rotator, -center);

	}

	bool Triangle::Render()
	{
		if (!isLoaded) return false;

		Engine::getShader().BindNewShader(shader_name);

		Engine::getRenderer().EnableBlend(true, BLEND_TYPE::SRC_ALPHA, BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

		Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], rotator, 1, false);

		Engine::getRenderer().BindVertexBuffer(VAIO);

		Engine::getRenderer().DrawArrays(DRAW_TYPE::TRIANGLES, (GLsizei)verts.size());

		Engine::getRenderer().UnbindVertexBuffer();

		Engine::getRenderer().EnableBlend(false);

		return true;
	}

	void Triangle::CleanUp()
	{

	}
}