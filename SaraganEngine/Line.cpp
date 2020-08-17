#include "EnginePCH.h"
#include "Line.h"

#include "Engine.h"
#include "Renderer.h"
#include "Shader.h"

Line::Line()
{
	isLoaded = false;
	vertexBuffer = 0;
	mouseLine = false;

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

void Line::Init(float x, float y, float x2, float y2, float z, glm::vec4 colour)
{
	this->origin.x = x;
	this->origin.y = y;
	this->direction.x = x2;
	this->direction.y = y2;
	this->colour = colour;

	Buffer.clear();
	vert dummy = { {this->origin.x,this->origin.y,z,1.0f},{-99.0f,-99.0f} };
	Buffer.push_back(dummy);
	vert dummy2 = { {this->direction.x,this->direction.y,z,1.0f},{-99.0f,-99.0f} };
	Buffer.push_back(dummy2);

	isLoaded = true;
}

void Line::Init(float x, float y, float angle)
{
	this->mouseLine = true;
	this->angle = angle;
	this->origin.x = x;
	this->origin.y = y;

	Buffer.clear();
	vert dummy = { {this->origin.x,this->origin.y,0.0f,1.0f},{-99.0f,-99.0f} };
	Buffer.push_back(dummy);

	this->direction.x = this->origin.x + cos(this->angle) * 100;
	this->direction.y = this->origin.y + sin(this->angle) * 100;

	vert dummy2 = { {this->direction.x,this->direction.y,0.0f,1.0f},{-99.0f,-99.0f} };
	Buffer.push_back(dummy2);

	isLoaded = true;
}

void Line::UpdatePos(float x, float y, std::vector<Line> hittest)
{
	this->origin.x = x;
	this->origin.y = y;

	Buffer.clear();
	vert dummy = { {this->origin.x,this->origin.y,0.0f,1.0f},{-99.0f,-99.0f} };
	Buffer.push_back(dummy);

	this->direction.x = this->origin.x + cos(this->angle) * 100;
	this->direction.y = this->origin.y + sin(this->angle) * 100;

	vert closest = vert();
	float last_distance = 0;

	for (size_t i = 0; i < hittest.size(); i++)
	{
		vert test;
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

	vert dummy2 = { {this->direction.x,this->direction.y,0.0f,1.0f},{-99.0f,-99.0f} };
	Buffer.push_back(dummy2);

	isLoaded = true;

}

bool Line::IntersectsLine(Line* line, vert& result)
{

	float dx = this->direction.x - this->origin.x;
	float dy = this->direction.y - this->origin.y;
	float da = line->direction.x - line->origin.x;
	float db = line->direction.y - line->origin.y;


	if (da * dy - db * dx != 0) {
		float s = (dx * (line->origin.y - this->origin.y) + dy * (this->origin.x - line->origin.x)) / (da * dy - db * dx);
		float t = (da * (this->origin.y - line->origin.y) + db * (line->origin.x - this->origin.x)) / (db * dx - da * dy);

		if (t >= 0 && (s >= 0) && (s <= 1)) {
			result = { {(this->origin.x + t * dx),(this->origin.y + t * dy),0.0f,1.0f},{-99.0f,-99.0f} };
			return true;
		}
	}

	return false;
}

void Line::Update(float dt)
{
	if (!isLoaded) return;

	if (vertexBuffer && hasUpdate) {
		Engine::getEngine().renderer->ReGenerateBuffer(VAOID[0], vertexBuffer, Buffer);

	}
	else if (!vertexBuffer || vertexBuffer == 0 || hasUpdate) {
		Engine::getEngine().renderer->GenerateBuffer(VAOID[0], vertexBuffer, Buffer);

		hasUpdate = true;
	}
}

bool Line::Render()
{
	if (!isLoaded) return false;

	if (Buffer.size() > 0) {

		Shader* s = Engine::getEngine().renderer->CurrentShader;

		if (this->mouseLine) {
			glUniform4fv(s->Color, 1, glm::value_ptr(this->mouseLineColour));
		}
		else {
			glUniform4fv(s->Color, 1, glm::value_ptr(this->colour));
		}

		glUniformMatrix4fv(s->modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glBindVertexArray(VAOID[0]); // Bind our Vertex Array Object

		glDrawArrays(GL_LINES, 0, (GLsizei)Buffer.size()); // Draw our line
				
		glBindVertexArray(0); // Unbind our Vertex Array Object
	}

	return true;
}

void Line::CleanUp()
{

}