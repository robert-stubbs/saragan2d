#ifndef _BATCH_RENDERER_H_
#define _BATCH_RENDERER_H_

#include "Types.h"
#include "TextureQuad.h"

namespace GameEngine
{

	class BatchRenderer
	{
		protected:
			int MaxQuadSize;
			int CurrentQuadSize;
			unsigned int VAO;
			unsigned int VBO;
			unsigned int IBO;
			std::vector<vert2D> verts;
			std::vector<int> indicies;

			std::string shader_name;

			int currentIndex;

		public:
			BatchRenderer() {}
			BatchRenderer(std::string shadername);

			virtual ~BatchRenderer();

			virtual void UnloadBuffers();

			virtual void Init(int max_quads = 1000);
			virtual void BeginBatch();
			virtual void EndBatch();

			virtual void AddQuad(TextureQuad quad);

			inline int MaxVertSize() { return MaxQuadSize * 4; }
			inline int MaxIndexSize() { return MaxQuadSize * 6; }
	};

}

#endif