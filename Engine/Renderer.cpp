#include "EnginePCH.h"
#include "Renderer.h"

#include "OpenGLRenderEngine.h"

namespace GameEngine {

	Renderer::Renderer()
	{
		engine_type = RenderEngines::None;
		render_engine = nullptr;
	}

	Renderer::Renderer(RenderEngines EngineType)
	{
		engine_type = EngineType;
		render_engine = nullptr;
	}

	Renderer::~Renderer()
	{
		SAFE_DELETE(render_engine);
	}

	bool Renderer::init()
	{		
		switch (engine_type)
		{
			case GameEngine::None:
				render_engine = nullptr;
				return false;
				break;
			case GameEngine::OpenGL:
				render_engine = new OpenGLRenderEngine();
				break;
			case GameEngine::DirectX:
				break;
		default:
			break;
		}

		render_engine->Init();

		return true;
	}

	bool Renderer::PostInit()
	{
		if (render_engine != nullptr) {
			render_engine->PostInit();
		}

		return true;
	}

	bool Renderer::RenderStart()
	{
		if (render_engine != nullptr) {
			render_engine->RenderStart();
			return true;
		}

		return false;
	}

	bool Renderer::Cleanup()
	{
		if (render_engine != nullptr) {
			render_engine->Cleanup();
		}

		SAFE_DELETE(render_engine);

		return true;
	}

	glm::vec3 Renderer::GetWorldPos(int x, int y, glm::mat4 projection, glm::mat4 view)
	{
		if (render_engine != nullptr) {
			return render_engine->GetWorldPos(x, y, projection, view);
		}

		return glm::vec3();
	}

	glm::vec3 Renderer::GetWorldPos2D(int x, int y, glm::mat4 projection, glm::mat4 view)
	{
		if (render_engine != nullptr) {
			return render_engine->GetWorldPos2D(x, y, projection, view);
		}

		return glm::vec3();
	}

	bool Renderer::ResizeWindow(int Width, int Height)
	{
		if (render_engine != nullptr) {
			return render_engine->ResizeWindow(Width, Height);
		}
		return false;
	}

	void Renderer::GenerateBuffer(unsigned int& VBO, std::vector<vert>& verts)
	{
		if (render_engine != nullptr) {
			render_engine->GenerateBuffer(VBO, verts);
		}
	}

	void Renderer::ReGenerateBuffer(unsigned int& VBO, std::vector<vert>& verts)
	{
		if (render_engine != nullptr) {
			render_engine->ReGenerateBuffer(VBO, verts);
		}
	}

	bool Renderer::UpdateBuffer(unsigned int& VBO, std::vector<vert>& verts)
	{
		if (render_engine != nullptr) {
			return render_engine->UpdateBuffer(VBO, verts);
		}

		return false;
	}

	void Renderer::UnbindVertexBuffer()
	{
		if (render_engine != nullptr) {
			render_engine->UnbindVertexBuffer();
		}
	}

	void Renderer::GenerateIndexBuffer(unsigned& IBO, std::vector<int>& VertIndex)
	{
		if (render_engine != nullptr) {
			render_engine->GenerateIndexBuffer(IBO, VertIndex);
		}
	}

	void Renderer::UnbindIndexBuffer()
	{
		if (render_engine != nullptr) {
			render_engine->UnbindIndexBuffer();
		}
	}
}