#ifndef _BATCH_RENDERER_H_
#define _BATCH_RENDERER_H_

#include "Types.h"

namespace GameEngine
{

	class BatchRenderer
	{
		private:
			int MaxQuadSize;
			unsigned int VAO;
			unsigned int VBO;
			unsigned int IBO;
			std::vector<vert2D> verts;
			std::vector<int> indicies;

			int currentIndex;

		public:

			BatchRenderer();
			virtual ~BatchRenderer();
			virtual void Init(int max_quads = 1000);
			virtual void BeginBatch();

			// TODO - Add Quad

			virtual void EndBatch();

	};

}

#endif