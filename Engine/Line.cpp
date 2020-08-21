#include "EnginePCH.h"
#include "Line.h"

#include "Engine.h"
#include "Renderer.h"
#include "Shader.h"

namespace GameEngine
{
	Line::Line()
	{
		shader_name = "DEFAULT2D";
		isLoaded = false;
		VBO = 0;
		mouseLine = false;
		verts = std::vector<vert2D>();
		colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		mouseLineColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	Line::~Line()
	{

	}

	void Line::Init()
	{
		isLoaded = true;

	}

	void Line::Init(float x, float y, float x2, float y2, float z, glm::vec4 col)
	{
		this->origin.x = x;
		this->origin.y = y;
		this->direction.x = x2;
		this->direction.y = y2;
		this->colour = col;

		verts.clear();
		vert2D dummy = { {this->origin.x,this->origin.y,z,1.0f},{-99.0f,-99.0f}, {colour.r, colour.g, colour.b, colour.a } };
		verts.push_back(dummy);
		vert2D dummy2 = { {this->direction.x,this->direction.y,z,1.0f},{-99.0f,-99.0f}, {colour.r, colour.g, colour.b, colour.a } };
		verts.push_back(dummy2);

		GenerateBuffers();
	}

	void Line::Init(float x, float y, float angle)
	{
		this->mouseLine = true;
		this->angle = angle;
		this->origin.x = x;
		this->origin.y = y;

		verts.clear();
		vert2D dummy = { {this->origin.x,this->origin.y,0.0f,1.0f},{-99.0f,-99.0f}, {mouseLineColour.r, mouseLineColour.g, mouseLineColour.b, mouseLineColour.a } };
		verts.push_back(dummy);

		this->direction.x = this->origin.x + cos(this->angle) * 100;
		this->direction.y = this->origin.y + sin(this->angle) * 100;

		vert2D dummy2 = { {this->direction.x,this->direction.y,0.0f,1.0f},{-99.0f,-99.0f}, {mouseLineColour.r, mouseLineColour.g, mouseLineColour.b, mouseLineColour.a } };
		verts.push_back(dummy2);

		isLoaded = true;
	}

	void Line::UpdatePos(float x, float y, std::vector<Line> hittest)
	{
		this->origin.x = x;
		this->origin.y = y;

		verts.clear();
		vert2D dummy = { {this->origin.x,this->origin.y,0.0f,1.0f},{-99.0f,-99.0f}, {mouseLineColour.r, mouseLineColour.g, mouseLineColour.b, mouseLineColour.a } };
		verts.push_back(dummy);

		this->direction.x = this->origin.x + cos(this->angle) * 100;
		this->direction.y = this->origin.y + sin(this->angle) * 100;

		vert2D closest = vert2D();
		float last_distance = 0;

		for (size_t i = 0; i < hittest.size(); i++)
		{
			vert2D test;
			if (this->IntersectsLine(&hittest[i], test)) {
				if (last_distance == 0) {
					closest = test;
					last_distance = glm::distance(this->origin, glm::vec3(closest.pos[0], closest.pos[1], closest.pos[2]));
				}
				else {
					float this_distance = glm::distance(this->origin, glm::vec3(test.pos[0], test.pos[1], test.pos[2]));
					if (this_distance < last_distance) {
						closest = test;
						last_distance = this_distance;
					}
				}
			}
		}

		this->direction.x = closest.pos[0];
		this->direction.y = closest.pos[1];

		vert2D dummy2 = { {this->direction.x,this->direction.y,0.0f,1.0f},{-99.0f,-99.0f}, {mouseLineColour.r, mouseLineColour.g, mouseLineColour.b, mouseLineColour.a } };
		verts.push_back(dummy2);

		GenerateBuffers();
		isLoaded = true;

	}

	bool Line::IntersectsLine(Line* line, vert2D& result)
	{

		float dx = this->direction.x - this->origin.x;
		float dy = this->direction.y - this->origin.y;
		float da = line->direction.x - line->origin.x;
		float db = line->direction.y - line->origin.y;


		if (da * dy - db * dx != 0) {
			float s = (dx * (line->origin.y - this->origin.y) + dy * (this->origin.x - line->origin.x)) / (da * dy - db * dx);
			float t = (da * (this->origin.y - line->origin.y) + db * (line->origin.x - this->origin.x)) / (db * dx - da * dy);

			if (t >= 0 && (s >= 0) && (s <= 1)) {
				result = { {(this->origin.x + t * dx),(this->origin.y + t * dy),0.0f,1.0f},{-99.0f,-99.0f}, {mouseLineColour.r, mouseLineColour.g, mouseLineColour.b, mouseLineColour.a } };
				return true;
			}
		}

		return false;
	}

	void Line::GenerateBuffers()
	{
		if (!VBO || VBO == 0)
		{
			glGenVertexArrays(1, &VAIO);
			glBindVertexArray(VAIO);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * verts.size(), &verts[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vert2D), 0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);


	/*			Engine::getRenderer().GenerateBuffer(VBO, verts);
			
			Shader& s = Engine::getShader()[shader_name];

	
			Engine::getRenderer().VertexStructurePointerF(s["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
		Engine::getRenderer().VertexStructurePointerF(s["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
			Engine::getRenderer().VertexStructurePointerF(s["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

			Engine::getRenderer().UnbindVertexBuffer();*/

			isLoaded = true;
		}
		else {
			Engine::getRenderer().UpdateBuffer(VBO, verts);
			Engine::getRenderer().UnbindVertexBuffer();
		}
	}

	void Line::Update(float dt)
	{
		if (!isLoaded) return;

		if (VBO && hasUpdate) {
			Engine::getRenderer().UpdateBuffer(VBO, verts);
			Engine::getRenderer().UnbindVertexBuffer();

		}
	}

	bool Line::Render()
	{
		if (!isLoaded) return false;

		if (hasUpdate) {
			hasUpdate = false;
		}

		if (verts.size() > 0 && VBO != 0) {

			//Engine::getShader().BindNewShader(shader_name);

			//Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);
			//Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["projectionMatrix"], glm::mat4(1.0f), 1, false);
			//Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["viewMatrix"], glm::mat4(1.0f), 1, false);
			Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);


			glBindVertexArray(VAIO); // Bind our Vertex Array Object

			glDrawArrays(GL_LINES, 0, (GLsizei)verts.size()); // Draw our line

			glBindVertexArray(0); // Unbind our Vertex Array Object

			//Engine::getRenderer().BindVertexBuffer(VBO);

			//Engine::getRenderer().DrawArrays(DRAW_TYPE::LINES, (GLsizei)verts.size());

			//Engine::getRenderer().UnbindVertexBuffer();

		}

		return true;
	}

	void Line::CleanUp()
	{

	}
}