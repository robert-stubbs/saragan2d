#ifndef _RENDER_ENGINE_BASE_H_
#define _RENDER_ENGINE_BASE_H_

#include "Types.h"

namespace GameEngine {
	class RenderEngineBase
	{
		public:

			RenderEngineBase();
			virtual ~RenderEngineBase();

			virtual bool Init() = 0;
			virtual bool PostInit() = 0;
			virtual void RenderStart() = 0;
			
			virtual bool Cleanup() = 0;

			virtual void CheckError() = 0;

			virtual glm::vec3 GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view) = 0;
			virtual glm::vec3 GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view) = 0;

			virtual bool ResizeWindow(int Width, int Height) = 0;

			virtual void GenerateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;
			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;
			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;
			virtual void UnbindVertexBuffer() = 0;

			virtual void GenerateIndexBuffer(unsigned& IBO, std::vector<int>& VertIndex) = 0;
			virtual void UnbindIndexBuffer() = 0;
	};
}

#endif // !_RENDERER_H_
