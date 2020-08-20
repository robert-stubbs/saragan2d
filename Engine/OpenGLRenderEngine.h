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
			virtual void GenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts);

			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert>& verts);
			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts);

			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts);
			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert2D>& verts);

			virtual void BindVertexBuffer(unsigned int& VBO);
			virtual void UnbindVertexBuffer();

			virtual void GenerateIndexBuffer(unsigned& IBO, std::vector<int>& VertIndex);

			virtual void BindIndexBuffer(unsigned int& IBO);
			virtual void UnbindIndexBuffer();

			// Buffer Structure Functions
			virtual void VertexStructurePointerF(int location, int size, bool normalized, int stride, const void* pointer = 0);

			// Binding uniforms to shader 
			virtual void UniformInt(int location, int value);
			virtual void UniformVec4(int location, glm::vec4& vector, int count = 1);
			virtual void UniformMat4(int location = 0, glm::mat4& transform = glm::mat4(1.0f), int size = 1, bool transpose = false);

			virtual void EnableBlend(bool enabled = true, BLEND_TYPE sfactor = BLEND_TYPE::SRC_ALPHA, BLEND_TYPE dfactor = BLEND_TYPE::ONE_MINUS_SRC_ALPHA);
			virtual void EnableDepthTest(bool enabled = true);

			virtual void DrawArrays(DRAW_TYPE type, int count, int first = 0);
			virtual void DrawElements(DRAW_TYPE type, int count, VALUE_TYPE indice_type = VALUE_TYPE::UNSIGNED_INT, const void* indices = 0);
	};
}

#endif // !_RENDERER_H_
