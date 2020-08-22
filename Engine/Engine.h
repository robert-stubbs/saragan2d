#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Context.h"
#include "Renderer.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "ShaderDef.h"
#include "Camera2D.h"
#include "EventManager.h"

#include "StateMachine.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "Font.h"
#include "Input.h"

namespace GameEngine {

	class Engine
	{
		private:
			Engine() {};

			Context ctx;
			Renderer renderer;
			ShaderManager shader_mgr;

			std::vector<std::shared_ptr<ShaderDef>> _shader_definitions;

		public:
			//StateMachine* GameFSM;
			SystemManager* System;
			EntityManager* EntityMgr;

			//Font* font;

			Camera2D* cam;
			~Engine();

			bool fullscreen = false;
			std::string asset_dir;

			PLATFORM _platform = PLATFORM::GLFW;
			RenderEngines _engine = RenderEngines::OpenGL;

			GLFWwindow* window;
			std::string WindowName = "";
			int WindowWidth = 0;
			int WindowHeight = 0;

			inline void SetPlatform(PLATFORM platform) { 
				_platform = platform; 
				Input::Get().SetPlatform(platform);
			};

			inline void SetRenderEngine(RenderEngines engine) { _engine = engine; };
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

			void TestFunction();

			void AddShaderDef(std::shared_ptr<ShaderDef> _def);

			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

			static ShaderManager& getShader() {
				return get().shader_mgr;
			}

			static Shader& getCurrentShader() {
				return get().shader_mgr.ShaderEngine();
			}

			static RenderEngineBase& getRenderer() {
				return get().renderer.RenderEngine();
			}

			static Context& getContext() {
				return get().ctx;
			}

			static EventManager& Events() {
				return EventManager::Instance();
			}

			static Engine& get() {
				//instantiate the engine
				static Engine instance;
				//return static instance
				return instance;
			}
			static inline Engine& getEngine() { return get(); }
		
	};
}

#endif