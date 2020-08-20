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

			Triangle();
			~Triangle();
			virtual void Init() override;
			virtual void Update(float dt) override;
			virtual bool Render() override;
			virtual void CleanUp() override;
	};
}

#endif