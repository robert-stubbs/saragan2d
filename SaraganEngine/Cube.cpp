#include "EnginePCH.h"
#include "Cube.h"

#include "Engine.h"
#include "Shader.h"
#include "Renderer.h"

Cube::Cube()
{
	hasTexture = false;
	isLoaded = false;
	VBO = 0;
	IBO = 0;
	VAIO = 0;
	colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	origin = glm::vec3(1.0f);
	height = 10;
	width = 10;

	texture = new Texture();
}

Cube::~Cube()
{

}

void Cube::Init()
{
	isLoaded = true;

}

void Cube::Init(float x, float y, float z, float width, float height)
{
	this->origin = glm::vec3(x, y, z);
	this->width = width;
	this->height = height;

	GenerateVerts();
}

void Cube::GenerateVerts()
{
	float x = this->origin.x;
	float y = this->origin.y;
	float z = this->origin.z;

	vert Floor1 = { {x,y + height,z,1.0f},					{0.0f, 0.0f} };
	vert Floor2 = { {x,y + height,z + width,1.0f},			{1.0f, 1.0f} };
	vert Floor3 = { {x + width,y + height,z + width,1.0f},	{0.43f,0.35f} };
	vert Floor4 = { {x + width,y + height,z,1.0f},			{0.26f,0.35f} };

	// floor
	vert Top1 = { {x,y,z,1.0f},						{0.0f, 0.0f} };
	vert Top2 = { {x,y,z + width,1.0f},				{0.0f, 1.0f} };
	vert Top3 = { {x + width,y,z + width,1.0f},		{0.43f,0.1f} };
	vert Top4 = { {x + width,y,z,1.0f},				{0.26f,0.1f} };

	verts.push_back(Floor1);
	verts.push_back(Floor2);
	verts.push_back(Floor3);
	verts.push_back(Floor4);
	verts.push_back(Top1);
	verts.push_back(Top2);
	verts.push_back(Top3);
	verts.push_back(Top4);

	//// RIGHT
	VertIndex.push_back(7);
	VertIndex.push_back(6);
	VertIndex.push_back(2);

	VertIndex.push_back(2);
	VertIndex.push_back(3);
	VertIndex.push_back(7);

	// TOP
	VertIndex.push_back(0);
	VertIndex.push_back(1);
	VertIndex.push_back(2);

	VertIndex.push_back(2);
	VertIndex.push_back(3);
	VertIndex.push_back(0);

	// BOTTOM
	VertIndex.push_back(4);
	VertIndex.push_back(5);
	VertIndex.push_back(6);

	VertIndex.push_back(6);
	VertIndex.push_back(7);
	VertIndex.push_back(4);

	// FRONT
	VertIndex.push_back(4);
	VertIndex.push_back(7);
	VertIndex.push_back(3);

	VertIndex.push_back(3);
	VertIndex.push_back(0);
	VertIndex.push_back(4);

	// BACK
	VertIndex.push_back(5);
	VertIndex.push_back(6);
	VertIndex.push_back(2);

	VertIndex.push_back(2);
	VertIndex.push_back(1);
	VertIndex.push_back(5);

	// LEFT
	VertIndex.push_back(4);
	VertIndex.push_back(5);
	VertIndex.push_back(1);

	VertIndex.push_back(1);
	VertIndex.push_back(0);
	VertIndex.push_back(4);


	isLoaded = true;
}
void Cube::Update(float dt)
{
	if (!isLoaded) return;

	if (!VBO || VBO == 0 || hasUpdate) {

		
		Engine::getEngine().renderer->GenerateIndexBuffer(VAIO, IBO, VBO, verts, VertIndex);
		hasUpdate = true;

		if (hasTexture) {
			texture->generateTgaStructBuffer();
		}
	}
}

bool Cube::Render()
{
	if (!isLoaded) return false;

	if (verts.size() > 0) {
		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);

		glUniform4fv(Engine::getEngine().renderer->CurrentShader->Color, 1, glm::value_ptr(this->colour));
		glUniformMatrix4fv(Engine::getEngine().renderer->CurrentShader->modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

		if (hasTexture) {
			if (Engine::getEngine().renderer->CurrentTextureID != texture->TextureID)
			{
				Engine::getEngine().renderer->CurrentTextureID = texture->TextureID;
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, Engine::getEngine().renderer->CurrentTextureID);
			}
		}

		glBindVertexArray(VAIO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glDrawElements(GL_TRIANGLES, (int)VertIndex.size(), GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	return true;
}

void Cube::CleanUp()
{

}


void Cube::SetupTexture(std::string path)
{
	texture = new Texture();
	texture->LoadTGAFromFile(path);
	hasTexture = true;
}