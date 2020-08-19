#ifndef _OPENGL_RENDER_ENGINE_H_
#define _OPENGL_RENDER_ENGINE_H_

#include "Types.h"
#include "RenderEngineBase.h"

namespace GameEngine {
	class OpenGLRenderEngine : public RenderEngineBase
	{
		public:

			OpenGLRenderEngine();
			virtual ~OpenGLRenderEngine();

			virtual bool Init();
			virtual bool PostInit();
			virtual void RenderStart();
			virtual bool Cleanup();
			
			virtual void CheckError();

			virtual glm::vec3 GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view);
			virtual glm::vec3 GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view);

			virtual bool ResizeWindow(int Width, int Height);

			virtual void GenerateBuffer(unsigned int& VBO, std::vector<vert>& verts);
			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert>& verts);
			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts);
			virtual void UnbindVertexBuffer();

			virtual void GenerateIndexBuffer(unsigned& IBO, std::vector<int>& VertIndex);
			virtual void UnbindIndexBuffer();
	};
}

#endif // !_RENDERER_H_
