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

			virtual void BindVertexBuffer(unsigned int& VBO);
			virtual void UnbindVertexBuffer();

			virtual void GenerateIndexBuffer(unsigned& IBO, std::vector<int>& VertIndex);

			virtual void BindIndexBuffer(unsigned int& IBO);
			virtual void UnbindIndexBuffer();

			// Buffer Structure Functions
			virtual void VertexStructurePointerF(int location, int size, bool normalized, int stride, const void* pointer = 0);

			// Binding uniforms to shader 
			virtual void UniformMat4(int location = 0, glm::mat4& transform = glm::mat4(1.0f), int size = 1, bool transpose = false);
	};
}

#endif // !_RENDERER_H_
