#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Renderer.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "ShaderDef.h"

namespace GameEngine {

	class Engine
	{
		private:
			Engine() {};

			Renderer renderer;
			ShaderManager shader_mgr;

			std::vector<std::shared_ptr<ShaderDef>> _shader_definitions;

		public:
			~Engine();

			bool fullscreen = false;
			std::string asset_dir;

			GLFWwindow* window;
			std::string WindowName = "";
			int WindowWidth = 0;
			int WindowHeight = 0;

			void SetAssetDir(std::string directory);
			void SetWindowName(std::string name);
			void SetWindowSize(int width, int height, bool isFullScreen = false);

			bool PreInit();
			bool Init();
			bool PostInit();
			bool Update(float DeltaTime);
			bool Update3D(float DeltaTime);
			bool UpdateOrth(float DeltaTime);

			void Render();
			void Render3D();
			void RenderOrth();
			void RenderEnd();
			bool Cleanup();

			void AddShaderDef(std::shared_ptr<ShaderDef> _def);

			static ShaderManager& getShader() {
				return get().shader_mgr;
			}

			static Shader& getCurrentShader() {
				return get().shader_mgr.ShaderEngine();
			}

			static RenderEngineBase& getRenderer() {
				return get().renderer.RenderEngine();
			}

			static Engine& get() {
				//instantiate the engine
				static Engine instance;
				//return static instance
				return instance;
			}
		
	};
}

#endif