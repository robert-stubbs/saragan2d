#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "Object.h"
#include "Types.h"

namespace GameEngine
{
	class Line;

	/*
		This class is really only intended for 2D
	*/
	class Square : public Object
	{
	public:
		Square();
		~Square();
		virtual void Init();
		virtual void Init(float x, float y, float width, float height, bool stroke = false, glm::vec4 strokeColour = glm::vec4());

		virtual void GenerateVerts();
		virtual void GenerateStroke();

		virtual void Update(float dt);
		virtual bool Render();
		virtual void CleanUp();

		virtual bool pointInSquare(float x, float y);

		GLuint		VAOID[1];
		GLuint		vertexBuffer;
		std::vector<vert2D> Buffer;

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