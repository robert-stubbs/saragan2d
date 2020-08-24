#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Types.h"
#include "Layer.h"
#include "RenderEngineBase.h"

namespace GameEngine {


	class Renderer : public Layer<RenderEngineBase>
	{
		public:
			Renderer();
			Renderer(RenderEngines EngineType);
			virtual void SetPlatform(PLATFORM platform) {};
			virtual ~Renderer();
	};

}

#endif
