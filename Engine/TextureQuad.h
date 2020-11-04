#ifndef _TEXTURE_QUAD_H_
#define _TEXTURE_QUAD_H_

#include "Object.h"
#include "Types.h"
#include "Texture.h"

namespace GameEngine
{
	class Line;

	/*
		This class is really only intended for 2D
	*/
	class TextureQuad : public Object
	{
	public:
		TextureQuad();
		~TextureQuad();
		virtual void Init();
		virtual void Init(float x, float y, float width, float height, float z_depth, glm::vec2 text_min, glm::vec2 text_max, glm::vec4 Color = glm::vec4());

		virtual void GenerateVerts();

		virtual void GenerateBuffers();

		virtual void Update(float dt);
		virtual bool Render();
		virtual void CleanUp();

		virtual bool pointInSquare(float x, float y);

		GLuint		VAIO;
		GLuint		VBO;
		std::vector<vert2D> verts;

		glm::vec3 origin;
		float width;
		float height;
		glm::vec2 texture_min;
		glm::vec2 texture_max;

		unsigned int texture_id = -1;

		glm::vec4 colour;
	};
}

#endif