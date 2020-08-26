#include "EnginePCH.h"
#include "OpenGLFont.h"
#include "Engine.h"

namespace GameEngine {

	OpenGLFont::OpenGLFont()
	{

	}

	OpenGLFont::~OpenGLFont()
	{
		texture_font_delete(font);
		glDeleteTextures(1, &atlas->id);
		atlas->id = 0;
		texture_atlas_delete(atlas);
	}

	void OpenGLFont::LoadFont(std::string name, float size)
	{
		filename = name;
		font = 0;
		atlas = texture_atlas_new(512, 512, 1);
		font = texture_font_new_from_file(atlas, size, filename.c_str());

		texture_glyph_t* g = texture_font_get_glyph(font, "A");
	}

	FontBuffer OpenGLFont::GetString(std::string s, float x, float y, glm::vec4 col)
	{
		FontBuffer f = FontBuffer();

		f.text = s;
		f.x = x;
		f.y = y;
		f.color = col;
		f.font = this->font;
		f.atlas = this->atlas;

		texture_font_load_glyphs(f.font, s.c_str());

		glm::vec2 pen = glm::vec2(x, y);
		pen.y -= f.font->height;

		int currentIndex = 0;
		for (int i = 0; i < (int)f.text.size(); ++i)
		{
			char* t = &(f.text.at(i));
			texture_glyph_t* glyph = texture_font_get_glyph(f.font, t);
			if (glyph != NULL)
			{
				float kerning = 0.0f;
				if (i > 0)
				{
					int previous = i - 1;
					kerning = texture_glyph_get_kerning(glyph, &f.text[previous]);
				}
				pen.x += kerning;
				float x0 = (float)(pen.x + glyph->offset_x);
				float y0 = (float)(pen.y - glyph->offset_y);
				float x1 = (float)(x0 + glyph->width);
				float y1 = (float)(y0 + glyph->height);
				float s0 = glyph->s0;
				float t0 = glyph->t0;
				float s1 = glyph->s1;
				float t1 = glyph->t1;

				vert2D vert0 = { { x0, y0, 1.0f, 1.0f }, { s0, t0 }, { col.r, col.g, col.b, col.a } };
				f.verts.push_back(vert0);

				vert2D vert1 = { { x0, y1, 1.0f, 1.0f }, { s0, t1 }, { col.r, col.g, col.b, col.a } };
				f.verts.push_back(vert1);

				vert2D vert2 = { { x1, y1, 1.0f, 1.0f }, { s1, t1 }, { col.r, col.g, col.b, col.a } };
				f.verts.push_back(vert2);

				vert2D vert3 = { { x1, y0, 1.0f, 1.0f }, { s1, t0 }, { col.r, col.g, col.b, col.a } };
				f.verts.push_back(vert3);

				f.VertIndex.push_back(currentIndex);
				f.VertIndex.push_back(currentIndex + 1);
				f.VertIndex.push_back(currentIndex + 2);

				f.VertIndex.push_back(currentIndex);
				f.VertIndex.push_back(currentIndex + 2);
				f.VertIndex.push_back(currentIndex + 3);

				currentIndex += 4;
				pen.x += glyph->advance_x;
			}
		}

		return f;
	}

	void OpenGLFont::GenerateBuffer(FontBuffer& buffer)
	{
		if (!buffer.loaded) {
			Engine::getRenderer().GenerateVertexArrayBuffer(buffer.VAIO);
			Engine::getRenderer().GenerateBuffer(buffer.VBO, buffer.verts);
			Engine::getRenderer().GenerateIndexBuffer(buffer.IBO, buffer.VertIndex);

			Shader& s = Engine::getShader()["DEFAULT2D"];
			Engine::getRenderer().VertexStructurePointerF(s["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
			Engine::getRenderer().VertexStructurePointerF(s["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
			Engine::getRenderer().VertexStructurePointerF(s["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

			// TODO - move this to the renderer
			glGenTextures(1, &buffer.atlas->id);
			glBindTexture(GL_TEXTURE_2D, buffer.atlas->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (int)buffer.atlas->width, (int)buffer.atlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer.atlas->data);

			Engine::getRenderer().UnbindBuffer();
			Engine::getRenderer().UnbindIndexBuffer();
			Engine::getRenderer().UnbindVertexBuffer();
			buffer.loaded = true;
		}
	}

	void OpenGLFont::RenderBuffer(FontBuffer& buffer)
	{
		if (buffer.loaded) {

			Engine::getRenderer().EnableBlend(true); 
			Engine::getRenderer().EnableDepthTest(true);

			Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);
			Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 1);
			Engine::getRenderer().BindVertexBuffer(buffer.VAIO);
			Engine::getRenderer().BindIndexBuffer(buffer.IBO);

			if (Engine::getRenderer().CurrentTextureID != buffer.atlas->id)
			{
				Engine::getRenderer().CurrentTextureID = buffer.atlas->id;
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, buffer.atlas->id);
			}

			Engine::getRenderer().DrawElements(GameEngine::DRAW_TYPE::TRIANGLES, (int)buffer.VertIndex.size(), GameEngine::VALUE_TYPE::UNSIGNED_INT, 0);

			Engine::getRenderer().UnbindIndexBuffer();
			Engine::getRenderer().UnbindVertexBuffer();
			Engine::getRenderer().UniformInt(Engine::getCurrentShader()["is_Text"], 0);

			Engine::getRenderer().EnableDepthTest(false);
			Engine::getRenderer().EnableBlend(false);
		}
	}
}