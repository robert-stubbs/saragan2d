#ifndef _SHADER_MANAGER_
#define _SHADER_MANAGER_

#include "Types.h"
#include "RenderEngineBase.h"
#include "Shader.h"
#include "Renderer.h"

namespace GameEngine {

	class ShaderManager
	{
		private:
			RenderEngines engine_type;
			//std::shared_ptr<Shader> shader_engine;
		public:

			ShaderManager();
			ShaderManager(RenderEngines EngineType);
			virtual ~ShaderManager();

			//Shader& RenderEngine() { return *shader_engine; }
	};

}

#endif
