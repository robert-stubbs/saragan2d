#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Types.h"
#include "RenderEngineBase.h"

namespace GameEngine {


	class Renderer
	{
		private:
			RenderEngines engine_type;
			std::shared_ptr<RenderEngineBase> render_engine;
		public:

			Renderer();
			Renderer(RenderEngines EngineType);
			virtual ~Renderer();

			RenderEngineBase& RenderEngine() { return *render_engine; }
	};

}

#endif
