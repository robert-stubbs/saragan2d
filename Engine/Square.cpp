#include "EnginePCH.h"
#include "Square.h"
#include "Engine.h"
#include "Shader.h"
#include "Renderer.h"
#include "Line.h"


namespace GameEngine
{
	Square::Square()
	{
		shader_name = "DEFAULT2D";
		isLoaded = false;
		vertexBuffer = 0;
		colour = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

		VAOID[0] = 0;

		origin = glm::vec3(1.0f);
		height = 10;
		width = 10;

		stroke = false;
		strokeColour = glm::vec4(1.0f);
		top = new Line();
		left = new Line();
		right = new Line();
		bottom = new Line();
	}

	Square::~Square()
	{

	}

	void Square::Init()
	{
		isLoaded = true;

	}

	void Square::Init(float x, float y, float width, float height, bool stroke, glm::vec4 strokeColour)
	{
		this->origin = glm::vec3(x, y, 0);
		this->width = width;
		this->height = height;

		GenerateVerts();

		if (stroke) {
			this->stroke = true;
			this->strokeColour = strokeColour;
			GenerateStroke();
		}
	}

	void Square::GenerateVerts()
	{
		vert2D tleft = { {this->origin.x,this->origin.y,0.0f,1.0f},{-99.0f,-99.0f}, {colour.r, colour.g, colour.b, colour.a } };

		vert2D tright = { {this->origin.x + this->width,this->origin.y,0.0f,1.0f},{-99.0f,-99.0f}, {colour.r, colour.g, colour.b, colour.a } };

		vert2D bright = { {this->origin.x + this->width,this->origin.y + this->height,0.0f,1.0f},{-99.0f,-99.0f}, {colour.r, colour.g, colour.b, colour.a } };

		vert2D bleft = { {this->origin.x,this->origin.y + this->height,0.0f,1.0f},{-99.0f,-99.0f}, {colour.r, colour.g, colour.b, colour.a } };

		Buffer.push_back(tleft);
		Buffer.push_back(tright);
		Buffer.push_back(bright);
		Buffer.push_back(bleft);

		isLoaded = true;
	}

	void  Square::GenerateStroke()
	{
		top->Init(this->origin.x + 1, this->origin.y + 1, this->origin.x + this->width - 1, this->origin.y + 1, 1.0f, this->strokeColour);
		left->Init(this->origin.x + 1, this->origin.y + 1, this->origin.x + 1, this->origin.y + this->height - 1, 1.0f, this->strokeColour);
		right->Init(this->origin.x + this->width, this->origin.y, this->origin.x + this->width, this->origin.y + this->height, 1.0f, this->strokeColour);
		bottom->Init(this->origin.x, this->origin.y + this->height, this->origin.x + this->width, this->origin.y + this->height, 1.0f, this->strokeColour);
	}

	void Square::Update(float dt)
	{
		if (!isLoaded) return;

		if (vertexBuffer && hasUpdate) {
			Engine::getRenderer().ReGenerateBuffer(vertexBuffer, Buffer);

			if (this->stroke) {
				top->colour = this->strokeColour;
				left->colour = this->strokeColour;
				right->colour = this->strokeColour;
				bottom->colour = this->strokeColour;

				top->Update(dt);
				left->Update(dt);
				right->Update(dt);
				bottom->Update(dt);
			}

		}
		else if (!vertexBuffer || vertexBuffer == 0 || hasUpdate) {

			Engine::getRenderer().GenerateBuffer(vertexBuffer, Buffer);

			Shader& s = Engine::getShader().BindNewShader(shader_name);
			Engine::getRenderer().VertexStructurePointerF(s["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
			Engine::getRenderer().VertexStructurePointerF(s["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
			Engine::getRenderer().VertexStructurePointerF(s["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

			if (this->stroke) {
				top->colour = this->strokeColour;
				left->colour = this->strokeColour;
				right->colour = this->strokeColour;
				bottom->colour = this->strokeColour;

				top->Update(dt);
				left->Update(dt);
				right->Update(dt);
				bottom->Update(dt);
			}

			hasUpdate = true;
		}
	}

	bool Square::Render()
	{
		if (!isLoaded) return false;

		if (Buffer.size() > 0) {


			Engine::getShader().BindNewShader(shader_name);

			Engine::getRenderer().BindVertexBuffer(vertexBuffer);

			Engine::getRenderer().DrawArrays(DRAW_TYPE::TRIANGLE_FAN, (GLsizei)Buffer.size());

			Engine::getRenderer().UnbindVertexBuffer();

			if (this->stroke) {
				top->Render();
				left->Render();
				right->Render();
				bottom->Render();
			}
		}

		return true;
	}

	void Square::CleanUp()
	{

	}

	bool Square::pointInSquare(float x, float y)
	{
		if (this->origin.x < x && this->origin.x + this->width > x) {
			if (this->origin.y < y && this->origin.y + this->height > y) {
				return true;
			}
		}
		return false;
	}
}