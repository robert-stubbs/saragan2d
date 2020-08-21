#include "EnginePCH.h"
#include "Text.h"

#include "Font.h"
#include "Engine.h"
#include "Renderer.h"
#include "Shader.h"
#include "SafeDelete.h"
#include "cErrorLogger.h"
#include "Dispatch.h"
namespace GameEngine
{

	Text::Text()
	{
		modelMatrix = glm::mat4(1.0f);
		//renderLevel = 1;
		m_type = "text";
		loaded = false;
		readyForBuffer = false;
	}

	Text::~Text()
	{
	}

	bool Text::Init()
	{
		return true;
	}

	void Text::SetString(Font* font, std::string s, float X, float Y, glm::vec4 col)
	{
		text = s;
		x = X;
		y = Y;
		color = col;
		f = font;

		texture_font_load_glyphs(f->font, s.c_str());

		glm::vec2 pen = glm::vec2(x, y);
		pen.y -= f->font->height;

		AddText(s, &pen);
		readyForBuffer = true;
	}

	void Text::AddText(std::string text, glm::vec2* pen)
	{
		int currentIndex = 0;
		for (int i = 0; i < (int)text.size(); ++i)
		{
			char* t = &(text.at(i));
			texture_glyph_t* glyph = texture_font_get_glyph(f->font, t);
			if (glyph != NULL)
			{
				float kerning = 0.0f;
				if (i > 0)
				{
					int previous = i - 1;
					kerning = texture_glyph_get_kerning(glyph, &text[previous]);
				}
				pen->x += kerning;
				float x0 = (float)(pen->x + glyph->offset_x);
				float y0 = (float)(pen->y - glyph->offset_y);
				float x1 = (float)(x0 + glyph->width);
				float y1 = (float)(y0 + glyph->height);
				float s0 = glyph->s0;
				float t0 = glyph->t0;
				float s1 = glyph->s1;
				float t1 = glyph->t1;

				vert vert0 = { { x0, y0, 1.0f, 1.0f }, { s0, t0 } };
				verts.push_back(vert0);

				vert vert1 = { { x0, y1, 1.0f, 1.0f }, { s0, t1 } };
				verts.push_back(vert1);

				vert vert2 = { { x1, y1, 1.0f, 1.0f }, { s1, t1 } };
				verts.push_back(vert2);

				vert vert3 = { { x1, y0, 1.0f, 1.0f }, { s1, t0 } };
				verts.push_back(vert3);

				VertIndex.push_back(currentIndex);
				VertIndex.push_back(currentIndex + 1);
				VertIndex.push_back(currentIndex + 2);

				VertIndex.push_back(currentIndex);
				VertIndex.push_back(currentIndex + 2);
				VertIndex.push_back(currentIndex + 3);

				currentIndex += 4;
				pen->x += glyph->advance_x;
			}
		}
	}

	void Text::changeText(std::string newText)
	{
		text = newText;

		verts.clear();
		VertIndex.clear();
		texture_font_load_glyphs(f->font, text.c_str());

		glm::vec2 pen = glm::vec2(x, y);
		pen.y -= f->font->height;

		AddText(text, &pen);

		//Engine::getEngine().renderer->GenerateIndexBuffer(VAIO, IBO, VBO, verts, VertIndex);
		glGenTextures(1, &f->atlas->id);
		glBindTexture(GL_TEXTURE_2D, f->atlas->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (int)f->atlas->width, (int)f->atlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, f->atlas->data);
	}

	void Text::Update(float dt)
	{
		if (!loaded && readyForBuffer) {
			//Engine::getEngine().renderer->GenerateIndexBuffer(VAIO, IBO, VBO, verts, VertIndex);

			glGenTextures(1, &f->atlas->id);
			glBindTexture(GL_TEXTURE_2D, f->atlas->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (int)f->atlas->width, (int)f->atlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, f->atlas->data);

			loaded = true;
		}
	}

	void Text::Render()
	{
		if (loaded) {
			/*glUniform1i(Engine::getEngine().renderer->CurrentShader->isText, 1);
			glUniform4fv(Engine::getEngine().renderer->CurrentShader->Color, 1, glm::value_ptr(color));
			glUniformMatrix4fv(Engine::getEngine().renderer->CurrentShader->modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
			glBindVertexArray(VAIO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

			if (Engine::getEngine().renderer->CurrentTextureID != f->atlas->id)
			{
				Engine::getEngine().renderer->CurrentTextureID = f->atlas->id;
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, Engine::getEngine().renderer->CurrentTextureID);
			}*/

			glDrawElements(GL_TRIANGLES, (int)VertIndex.size(), GL_UNSIGNED_INT, 0);


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			//glUniform1i(Engine::getEngine().renderer->CurrentShader->isText, 0);
		}
	}

	bool Text::handleMessage(SystemMessage msg)
	{
		return false;
	}

	void Text::CleanUp()
	{

	}
}