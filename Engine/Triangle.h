#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Object.h"
#include "Types.h"

namespace GameEngine {

	class Triangle : public Object
	{
		public:
			std::vector<vert2D> verts = std::vector<vert2D>();
			unsigned int        VBO;
			unsigned int        VAIO;

			glm::mat4 rotator;
			glm::vec3 origin;
			glm::vec3 center;

			Triangle();
			~Triangle();
			virtual void Init();
			virtual void Init(float x1, float y1, float x2, float y2, float x3, float y3);
			virtual void Update(float dt) override;
			virtual bool Render() override;
			virtual void CleanUp() override;
	};
}

#endif