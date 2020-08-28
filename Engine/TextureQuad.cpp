#include "EnginePCH.h"
#include "TextureQuad.h"
#include "Engine.h"
#include "Shader.h"
#include "Renderer.h"
#include "Line.h"
#include "Types.h"
#include "Texture.h"

namespace GameEngine
{
	TextureQuad::TextureQuad()
	{
		shader_name = "DEFAULT2D";
		isLoaded = false;
		VBO = 0;
		colour = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

		VAIO = 0;

		origin = glm::vec3(1.0f);
		height = 10;
		width = 10;
	}

	TextureQuad::~TextureQuad()
	{

	}

	void TextureQuad::Init()
	{
		isLoaded = true;

	}

	void TextureQuad::Init(float x, float y, float width, float height, glm::vec4 strokeColour)
	{
		this->origin = glm::vec3(x, y, 0);
		this->width = width;
		this->height = height;

		GenerateVerts();

		GenerateBuffers();

		text = Texture();
		if (text.LoadFile(Engine::get().asset_dir + "Textures/testsprite.png", TEXTURETYPES::SARAGAN_PNG))
		{
			text.GenerateAlphaBuffer();
		}
	}

	void TextureQuad::GenerateVerts()
	{
		vert2D tleft = { {this->origin.x,this->origin.y,0.0f,1.0f},{0.0f,0.1f}, {colour.r, colour.g, colour.b, colour.a } };

		vert2D tright = { {this->origin.x + this->width,this->origin.y,0.0f,1.0f},{0.07f,0.1f}, {colour.r, colour.g, colour.b, colour.a } };

		vert2D bright = { {this->origin.x + this->width,this->origin.y + this->height,0.0f,1.0f},{0.07f,0.15f}, {colour.r, colour.g, colour.b, colour.a } };

		vert2D bleft = { {this->origin.x,this->origin.y + this->height,0.0f,1.0f},{0.0f,0.15f}, {colour.r, colour.g, colour.b, colour.a } };

		verts.push_back(tleft);
		verts.push_back(tright);
		verts.push_back(bright);
		verts.push_back(bleft);

		isLoaded = true;
	}

	void TextureQuad::GenerateBuffers()
	{
		if (!VBO || VBO == 0)
		{
			Shader& s = Engine::getShader()[shader_name];

			Engine::getRenderer().GenerateVertexArrayBuffer(VAIO);
			Engine::getRenderer().GenerateBuffer(VBO, verts);

			Engine::getRenderer().VertexStructurePointerF(s["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
			Engine::getRenderer().VertexStructurePointerF(s["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
			Engine::getRenderer().VertexStructurePointerF(s["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

			Engine::getRenderer().UnbindBuffer();

			Engine::getRenderer().UnbindVertexBuffer();

			isLoaded = true;
		}
		else {
			Engine::getRenderer().UpdateBuffer(VBO, verts);
			Engine::getRenderer().UnbindBuffer();
		}
	}

	void TextureQuad::Update(float dt)
	{
		if (!isLoaded) return;
	}

	bool TextureQuad::Render()
	{
		if (!isLoaded) return false;

		if (!VBO || VBO == 0) {
			hasUpdate = true;
		}

		if (VAIO && VAIO > 0 && verts.size() > 0) {

			Engine::getShader().BindNewShader(shader_name);

			Engine::getRenderer().EnableBlend(true, BLEND_TYPE::SRC_ALPHA, BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

			if (Engine::getRenderer().CurrentTextureID != text.TextureID)
			{
				Engine::getRenderer().CurrentTextureID = text.TextureID;

				Engine::getRenderer().BindTextureBuffer(text.TextureID);
			}

			Engine::getRenderer().BindVertexBuffer(VAIO);

			Engine::getRenderer().DrawArrays(DRAW_TYPE::TRIANGLE_FAN, (GLsizei)verts.size());

			Engine::getRenderer().EnableBlend(false);
		}

		return true;
	}

	void TextureQuad::CleanUp()
	{

	}

	bool TextureQuad::pointInSquare(float x, float y)
	{
		if (this->origin.x < x && this->origin.x + this->width > x) {
			if (this->origin.y < y && this->origin.y + this->height > y) {
				return true;
			}
		}
		return false;
	}
}