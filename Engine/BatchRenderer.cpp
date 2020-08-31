#include "EnginePCH.h"
#include "BatchRenderer.h"
#include "Engine.h"
#include "Types.h"

namespace GameEngine
{
	BatchRenderer::BatchRenderer(std::string shadername)
	{
		MaxQuadSize = 0;
		VAO = 0;
		VBO = 0;
		IBO = 0;
		currentIndex = 0;
		verts = std::vector<vert2D>();
		indicies = std::vector<int>();
		shader_name = shadername;
	}

	BatchRenderer::~BatchRenderer()
	{
		// TODO - write a delete index buffer function

		// engine clean up buffers
		Engine::getRenderer().DeleteBuffer(VBO);
		Engine::getRenderer().DeleteVertexBuffer(VAO);
	}

	void BatchRenderer::Init(int max_quads)
	{
		// set size of our verts
		// set size of our indicies
		// buffer empty vert stack
		// generate indicies

		MaxQuadSize = max_quads;

		int max_verts = MaxVertSize();
		int max_indicies = MaxIndexSize();

		Shader& s = Engine::getShader()[shader_name];

		Engine::getRenderer().GenerateVertexArrayBuffer(VAO);
		Engine::getRenderer().GenerateEmptyBuffer(VBO, max_verts * sizeof(vert2D));

		Engine::getRenderer().VertexStructurePointerF(s["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
		Engine::getRenderer().VertexStructurePointerF(s["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
		Engine::getRenderer().VertexStructurePointerF(s["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

		int counter = 0;
		for (int i = 0; i < MaxQuadSize; i += 6)
		{
			indicies.push_back(i + 0);
			indicies.push_back(i + 1);
			indicies.push_back(i + 2);

			indicies.push_back(i + 2);
			indicies.push_back(i + 3);
			indicies.push_back(i + 0);

			counter += 4;
		}

		Engine::getRenderer().GenerateIndexBuffer(IBO, indicies);

		Engine::getRenderer().UnbindBuffer();
		Engine::getRenderer().UnbindIndexBuffer();
		Engine::getRenderer().UnbindVertexBuffer();
	}

	void BatchRenderer::BeginBatch()
	{
		// clear current index
		currentIndex = 0;
		CurrentQuadSize = 0;
		verts.clear();
	}

	void BatchRenderer::EndBatch()
	{
		Engine::getRenderer().BufferSubData(VBO, verts);

		Engine::getRenderer().BindVertexBuffer(VAO);
		Engine::getRenderer().BindIndexBuffer(IBO);

		// flush/render data
		Engine::getRenderer().DrawElements(GameEngine::DRAW_TYPE::TRIANGLES, currentIndex);
		
		Engine::getRenderer().UnbindIndexBuffer();
		Engine::getRenderer().UnbindVertexBuffer();
	}
	
	void BatchRenderer::AddQuad(TextureQuad quad)
	{
		if (CurrentQuadSize >= MaxQuadSize) {
			EndBatch();
			BeginBatch();
		}

		std::vector<vert2D>& v = quad.verts;
		verts.insert(verts.end(), v.begin(), v.end());
	}
}