#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Types.h"
#include "RenderEngineBase.h"

namespace GameEngine {

	enum RenderEngines
	{
		None = 0,
		OpenGL,
		DirectX
	};

	class Renderer
	{
		private:
			RenderEngines engine_type;
			RenderEngineBase* render_engine;
		public:

			Renderer();
			Renderer(RenderEngines EngineType);
			virtual ~Renderer();


			virtual bool init();
			virtual bool PostInit();
			virtual bool RenderStart();
			virtual bool Cleanup();

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

#endif
