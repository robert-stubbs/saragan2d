#ifndef _SHADER_MANAGER_
#define _SHADER_MANAGER_

#include "Types.h"
#include "Layer.h"
#include "Shader.h"
#include "Renderer.h"

namespace GameEngine {

	class ShaderManager : public Layer<Shader>
	{
		private:
			std::map<std::string, std::shared_ptr<Shader>> _shaders;
		public:

			ShaderManager();
			ShaderManager(RenderEngines EngineType);
			virtual ~ShaderManager();

			virtual void SetPlatform(PLATFORM platform) {};

			Shader& CreateShaderSpace(std::string name);

			Shader& operator[](std::string name);

			Shader& BindNewShader(std::string name);

			void BindShaderStructure();

	};

}

#endif
