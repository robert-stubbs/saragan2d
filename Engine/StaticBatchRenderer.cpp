#include "EnginePCH.h"
#include "StaticBatchRenderer.h"
#include "Engine.h"
#include "Types.h"

namespace GameEngine
{
	StaticBatchRenderer::StaticBatchRenderer(std::string shadername) : BatchRenderer(shadername)
	{
	}

	void StaticBatchRenderer::BeginBatch()
	{
		// clear current index
		currentIndex = 0;
		CurrentQuadSize = 0;
		verts.clear();
		verts = std::vector<vert2D>();
	}

	void StaticBatchRenderer::EndBatch()
	{
		if (verts.size() == 0) {
			return;
		}

		Engine::getRenderer().BufferSubData(VBO, verts);
	}

	void StaticBatchRenderer::RenderBatch()
	{
		if (verts.size() == 0) {
			return;
		}

		Engine::getRenderer().BindVertexBuffer(VAO);
		Engine::getRenderer().BindIndexBuffer(IBO);

		// flush/render data
		Engine::getRenderer().DrawElements(GameEngine::DRAW_TYPE::TRIANGLES, currentIndex);

		Engine::getRenderer().UnbindIndexBuffer();
		Engine::getRenderer().UnbindVertexBuffer();
	}
}