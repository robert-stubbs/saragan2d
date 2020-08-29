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
		virtual void Init(float x, float y, float width, float height, bool stroke = false, glm::vec4 strokeColour = glm::vec4());

		virtual void GenerateVerts();
		virtual void GenerateStroke();

		virtual void GenerateBuffers();

		virtual void Update(float dt);
		virtual bool Render();
		virtual void CleanUp();

		virtual bool pointInSquare(float x, float y);

		GLuint		VAIO;
		GLuint		VBO;
		std::vector<vert2D> verts;

		Texture text;

		glm::vec3 origin;
		float width;
		float height;

		glm::vec4 colour;

		bool stroke;
		glm::vec4 strokeColour;

		Line* top;
		Line* left;
		Line* right;
		Line* bottom;

	};
}

#endif