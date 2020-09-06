#ifndef _STATIC_BATCH_RENDERER_H_
#define _STATIC_BATCH_RENDERER_H_

#include "Types.h"
#include "TextureQuad.h"
#include "BatchRenderer.h"

namespace GameEngine
{

	class StaticBatchRenderer : public BatchRenderer
	{
	public:
		StaticBatchRenderer() {}
		StaticBatchRenderer(std::string shadername);
		virtual void BeginBatch() override;
		virtual void EndBatch() override;
		virtual void RenderBatch();
	};

}

#endif