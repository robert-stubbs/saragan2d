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
			
			// IF WINDOWS THIS - this generally i think is only used for raw openGL not glfw
			virtual void SetCurrentContext(HGLRC hRC, HDC hDC);

			virtual void CheckError();

			virtual glm::vec3 GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view);
			virtual glm::vec3 GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view);

			virtual bool ResizeWindow(int Width, int Height);
			
			// Vertex Array Buffers
			virtual void GenerateVertexArrayBuffer(unsigned int& VAO) override;
			virtual void DeleteVertexBuffer(unsigned int& VAO) override;
			virtual void BindVertexBuffer(unsigned int& VAO) override;
			virtual void UnbindVertexBuffer() override;

			// Vertex Buffers
			virtual void GenerateBuffer(unsigned int& VBO, std::vector<vert>& verts) override;
			virtual void GenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts) override;
			virtual void GenerateEmptyBuffer(unsigned int& VBO, int size) override;
			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert>& verts) override;
			virtual void ReGenerateBuffer(unsigned int& VBO, std::vector<vert2D>& verts) override;
			virtual void BufferSubData(unsigned int& VBO, std::vector<vert2D>& verts) override;
			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts) override;
			virtual bool UpdateBuffer(unsigned int& VBO, std::vector<vert2D>& verts) override;
			virtual void BindBuffer(unsigned int& VBO) override;
			virtual void UnbindBuffer() override;


			// Index Buffers
			virtual void GenerateIndexBuffer(unsigned int& IBO, std::vector<int>& VertIndex) override;
			virtual void BindIndexBuffer(unsigned int& IBO) override;
			virtual void UnbindIndexBuffer() override;
			virtual void DeleteBuffer(unsigned int& VAB) override;

			// Texture Buffers
			virtual void GenerateTextureBuffer(unsigned int& TBO, int width, int height, void* data, COLOR_TYPE internalformat, COLOR_TYPE format, VALUE_TYPE type) override;
			virtual void BindTextureBuffer(unsigned int& TBO) override;
			virtual void BindTextureBufferParams(TEXTURE_TARGET target, TEXTURE_TARGET_NAME name, TEXTURE_TARGET_PARAM param) override;
			virtual void GenerateTextureMipmap() override;
			virtual void UnbindTextureBuffer() override;

			// Frame buffer
			virtual void GenerateFrameBuffer(unsigned int& FBO) override;
			virtual void BindFrameBuffer(unsigned int& FBO) override;
			virtual void ResizeFrameBuffer(unsigned int& FBO, unsigned int& FBOTexture, float width, float height) override;
			virtual void UnbindFrameBuffer() override;
			virtual void DeleteFrameBuffer(unsigned int& FBO) override;
			virtual bool FrameBufferComplete() override;
			virtual void GenerateFrameBufferTexture(unsigned int& TextureID, float width, float height) override;
			virtual void BindTextureToFrameBuffer(unsigned int& TextureID) override;
			virtual void GenerateRenderBuffer(unsigned int& RBO) override;


			// Buffer Structure Functions
			virtual void VertexStructurePointerF(int location, int size, bool normalized, int stride, const void* pointer = 0);

			// Binding uniforms to shader 
			virtual void UniformInt(int location, int value);
			virtual void UniformVec4(int location, glm::vec4& vector, int count = 1);
			virtual void UniformMat4(int location = 0, glm::mat4& transform = glm::mat4(1.0f), int size = 1, bool transpose = false);

			virtual void EnableBlend(bool enabled = true, BLEND_TYPE sfactor = BLEND_TYPE::SRC_ALPHA, BLEND_TYPE dfactor = BLEND_TYPE::ONE_MINUS_SRC_ALPHA);
			virtual void EnableDepthTest(bool enabled = true);

			virtual void DrawArrays(DRAW_TYPE type, int count, int first = 0);

			virtual void DrawElements(DRAW_TYPE type, int count, VALUE_TYPE indice_type = VALUE_TYPE::UNSIGNED_INT, void* offset = 0);
			virtual void DrawIntElements(DRAW_TYPE type, int count, int offset = 0);
			virtual void DrawByteElements(DRAW_TYPE type, int count, unsigned char offset = 0);
			virtual void DrawShortElements(DRAW_TYPE type, int count, short offset = 0);
	};
}

#endif // !_RENDERER_H_
