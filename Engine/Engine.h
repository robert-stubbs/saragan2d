#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Context.h"
#include "Renderer.h"
#include "GUI.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "ShaderDef.h"
#include "Camera2D.h"
#include "EventManager.h"

#include "StateMachine.h"
#include "SystemManager.h"
#include "Font.h"
#include "Input.h"


#define PI  3.141592654
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.01745329251994329576923690768489

#define DEG2RAD(a)	(PI/180*(a))
#define RAD2DEG(a)	(180/PI*(a))

namespace GameEngine {

	class Engine
	{
		private:
			Engine() {};

			Context ctx;
			Renderer renderer;
			GUI* _gui;
			ShaderManager shader_mgr;
			StateMachine GameFSM;

			std::vector<std::shared_ptr<ShaderDef>> _shader_definitions;

		public:
			//
			SystemManager* System;
			//EntityManager* EntityMgr;

			//Font* font;

			Camera2D* cam;
			~Engine();

			float current_dt;

			bool fullscreen = false;
			std::string asset_dir;

			PLATFORM _platform = PLATFORM::GLFW;
			RenderEngines _engine = RenderEngines::OpenGL;

			std::string WindowName = "";
			int WindowWidth = 0;
			int WindowHeight = 0;

			inline void SetPlatform(PLATFORM platform) { 
				_platform = platform; 
				Input::GetInput().SetPlatform(platform);
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
			bool Cleanup();

			void KeyDown(int Key);
			void KeyUp(int Key);
			void MouseDown(int button);
			void MouseUp(int button);
			void MouseMove(float x, float y);

			void TestFunction();

			void AddShaderDef(std::shared_ptr<ShaderDef> _def);

			static StateMachine& state() {
				return get().GameFSM;
			}

			static GUIPlatform& getGUI() {
				return get()._gui->Get();
			}

			static ShaderManager& getShader() {
				return get().shader_mgr;
			}

			static Shader& getCurrentShader() {
				return get().shader_mgr.Get();
			}

			static RenderEngineBase& getRenderer() {
				return get().renderer.Get();
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