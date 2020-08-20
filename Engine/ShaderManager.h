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
			std::shared_ptr<Shader> current_shader;

			std::map<std::string, std::shared_ptr<Shader>> _shaders;
		public:

			ShaderManager();
			ShaderManager(RenderEngines EngineType);
			virtual ~ShaderManager();

			Shader& CreateShaderSpace(std::string name);

			Shader& operator[](std::string name);

			Shader& BindNewShader(std::string name);

			Shader& ShaderEngine() { return *current_shader; }
	};

}

#endif
