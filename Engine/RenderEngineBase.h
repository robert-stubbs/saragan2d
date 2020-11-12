#ifndef _RENDER_ENGINE_BASE_H_
#define _RENDER_ENGINE_BASE_H_

#include "Types.h"

namespace GameEngine {
	class RenderEngineBase
	{
		public:
			unsigned int CurrentTextureID = -1;

			unsigned int TextureArray[MAX_TEXTURES];

			float frame_buffer_width = 0.0f;
			float frame_buffer_height = 0.0f;

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
			virtual glm::vec3 GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view, float vpx, float vpy, float vpx2, float vpy2) = 0;

			virtual bool ResizeWindow(int Width, int Height) = 0;

			// Vertex Array Buffers
			virtual void GenerateVertexArrayBuffer(unsigned int& VAO) = 0;
			virtual void DeleteVertexBuffer(unsigned int& VAO) = 0;
			virtual void BindVertexBuffer(unsigned int& VAO) = 0;
			virtual void UnbindVertexBuffer() = 0;

			// Vertex Buffers
			virtual void GenerateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;
			virtual void GenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts) = 0;
			virtual void GenerateEmptyBuffer(unsigned int& VBO, int size) = 0;
			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;
			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts) = 0;
			virtual void BufferSubData(unsigned int& VBO, std::vector<vert2D>& verts) = 0;
			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts) = 0;
			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert2D>& verts) = 0;
			virtual void BindBuffer(unsigned int& VBO) = 0;
			virtual void UnbindBuffer() = 0;


			// Index Buffers
			virtual void GenerateIndexBuffer(unsigned int& IBO, std::vector<int>& VertIndex) = 0;
			virtual void BindIndexBuffer(unsigned int& IBO) = 0;
			virtual void UnbindIndexBuffer() = 0;
			virtual void DeleteBuffer(unsigned int& VAB) = 0;

			// Texture Buffers
			virtual void GenerateTextureBuffer(unsigned int& TBO, int width, int height, void* data, COLOR_TYPE internalformat, COLOR_TYPE format, VALUE_TYPE type) = 0;
			virtual void BindTextureBuffer(unsigned int& TBO) = 0;
			virtual void BindTextureBufferParams(TEXTURE_TARGET target, TEXTURE_TARGET_NAME name, TEXTURE_TARGET_PARAM param) = 0;
			virtual void GenerateTextureMipmap() = 0;
			virtual void UnbindTextureBuffer() = 0;

			virtual void GenerateTextureArrayBuffer(unsigned int& TBO, int width, int height, int number_of_textures, COLOR_TYPE internalformat, COLOR_TYPE format, VALUE_TYPE type) = 0;
			virtual void AddTextureToArrayBuffer(unsigned int& TBO, int width, int height, int index, void* data, COLOR_TYPE format, VALUE_TYPE type) = 0;
			virtual void ClearTextureArray() = 0;

			// Frame buffer
			virtual void GenerateFrameBuffer(unsigned int& FBO) = 0;
			virtual void BindFrameBuffer(unsigned int& FBO) = 0;
			virtual void ResizeFrameBuffer(unsigned int& FBO, unsigned int& FBOTexture, float width, float height) = 0;
			virtual void UnbindFrameBuffer() = 0;
			virtual void DeleteFrameBuffer(unsigned int& FBO) = 0;
			virtual bool FrameBufferComplete() = 0;
			virtual void GenerateFrameBufferTexture(unsigned int& TextureID, float width, float height) = 0;
			virtual void BindTextureToFrameBuffer(unsigned int& TextureID) = 0;
			virtual void GenerateRenderBuffer(unsigned int& RBO) = 0;

			// Buffer Structure Functions
			virtual void VertexStructurePointerF(int location, int size, bool normalized, int stride, const void* pointer) = 0;

			// Binding uniforms to shader 
			virtual void UniformInt(int location, int value) = 0;
			virtual void UniformVec4(int location, glm::vec4& vector, int count = 1) = 0;
			virtual void UniformMat4(int location, glm::mat4& transform, int size, bool transpose) = 0;

			virtual void EnableBlend(bool enabled = true, BLEND_TYPE sfactor = BLEND_TYPE::SRC_ALPHA, BLEND_TYPE dfactor = BLEND_TYPE::ONE_MINUS_SRC_ALPHA) = 0;
			virtual void EnableDepthTest(bool enabled = true) = 0;

			virtual void DrawArrays(DRAW_TYPE type, int count, int first = 0) = 0;

			virtual void DrawElements(DRAW_TYPE type, int count, VALUE_TYPE indice_type = VALUE_TYPE::UNSIGNED_INT, void* offset = 0) = 0;
			virtual void DrawIntElements (DRAW_TYPE type, int count, int offset = 0) = 0;
			virtual void DrawByteElements(DRAW_TYPE type, int count, unsigned char offset = 0) = 0;
			virtual void DrawShortElements(DRAW_TYPE type, int count, short offset = 0) = 0;
			
	};
}

#endif // !_RENDERER_H_
