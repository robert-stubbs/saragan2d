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

			// TODO if windows this
			virtual void SetCurrentContext(HGLRC hRC, HDC hDC) = 0;
			
			virtual bool Cleanup() = 0;

			virtual void CheckError() = 0;

			virtual glm::vec3 GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view) = 0;
			virtual glm::vec3 GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view) = 0;

			virtual bool ResizeWindow(int Width, int Height) = 0;

			virtual void GenerateVertexArrayBuffer(unsigned int& VAB) = 0;

			virtual void DeleteBuffer(unsigned int& VAB) = 0;
			virtual void DeleteVertexBuffer(unsigned int& VAO) = 0;

			virtual void GenerateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;
			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;
			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;

			virtual void GenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts) = 0;
			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts) = 0;
			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert2D>& verts) = 0;

			virtual void BindVertexBuffer(unsigned int& VBO) = 0;
			virtual void UnbindVertexBuffer() = 0;

			virtual void BindBuffer(unsigned int& VBO) = 0;
			virtual void UnbindBuffer() = 0;

			virtual void GenerateIndexBuffer(unsigned& IBO, std::vector<int>& VertIndex) = 0;
			virtual void BindIndexBuffer(unsigned int& IBO) = 0;
			virtual void UnbindIndexBuffer() = 0;

			// Buffer Structure Functions
			virtual void VertexStructurePointerF(int location, int size, bool normalized, int stride, const void* pointer) = 0;

			// Binding uniforms to shader 
			virtual void UniformInt(int location, int value) = 0;
			virtual void UniformVec4(int location, glm::vec4& vector, int count = 1) = 0;
			virtual void UniformMat4(int location, glm::mat4& transform, int size, bool transpose) = 0;

			virtual void EnableBlend(bool enabled = true, BLEND_TYPE sfactor = BLEND_TYPE::SRC_ALPHA, BLEND_TYPE dfactor = BLEND_TYPE::ONE_MINUS_SRC_ALPHA) = 0;
			virtual void EnableDepthTest(bool enabled = true) = 0;

			virtual void DrawArrays(DRAW_TYPE type, int count, int first = 0) = 0;
			virtual void DrawElements (DRAW_TYPE type, int count, VALUE_TYPE indice_type = VALUE_TYPE::UNSIGNED_INT, const void* indices = 0) = 0;

	};
}

#endif // !_RENDERER_H_