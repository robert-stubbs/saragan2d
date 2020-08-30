#include "EnginePCH.h"
#include "BatchRenderer.h"

namespace GameEngine
{

	BatchRenderer::BatchRenderer()
	{
		MaxQuadSize = 0;
		VAO = 0;
		VBO = 0;
		IBO = 0;
		currentIndex = 0;
		verts = std::vector<vert2D>();
		indicies = std::vector<int>();
	}

	BatchRenderer::~BatchRenderer()
	{
		// engine clean up buffers
	}

	void BatchRenderer::Init(int max_quads)
	{
		MaxQuadSize = max_quads;
		// set size of our verts
		// set size of our indicies
		// buffer empty vert stack
		// generate indicies
	}

	void BatchRenderer::BeginBatch()
	{
		// clear current index
		currentIndex = 0;
	}

	void BatchRenderer::EndBatch()
	{
		// flush/render data
	}
}