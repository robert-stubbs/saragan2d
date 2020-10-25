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
#include "EntityManager.h"
#include "SystemManager.h"
#include "Font.h"
#include "Input.h"
#include "cErrorLogger.h"
#include "FileManager.h"

#include "World.h"


#define PI  3.141592654
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.01745329251994329576923690768489

#define DEG2RAD(a)	(PI/180*(a))
#define RAD2DEG(a)	(180/PI*(a))

#define LOG(a) Engine::Log()->WriteToConsole(a);

namespace GameEngine {

	class Engine
	{
		private:
			Engine() {
				log->CreateConsole();
				RenderToFrameBuffer = false;
				FBO = 0;
			};

			Context ctx;
			Renderer renderer;
			GUI* _gui;
			ShaderManager shader_mgr;
			StateMachine GameFSM;

			FileManager _file_manager;

			cErrorLogger* log = new cErrorLogger();

			std::vector<std::shared_ptr<ShaderDef>> _shader_definitions;

		public:
			//
			SystemManager* System;

			bool EditorFocusViewport;
			bool RenderToFrameBuffer;
			unsigned int FBO;
			unsigned int FBOTexture;
			unsigned int RBO;

			Camera2D* default_cam;
			Camera2D* current_cam;

			World w;

			~Engine();

			float current_dt;

			bool fullscreen = false;
			std::string asset_dir;

			PLATFORM _platform = PLATFORM::GLFW;
			RenderEngines _engine = RenderEngines::OpenGL;

			std::string WindowName = "";
			int WindowWidth = 0;
			int WindowHeight = 0;
			float RenderWidth = 0;
			float RenderHeight = 0;
			bool loaded = false;

			inline void SetPlatform(PLATFORM platform) { 
				_platform = platform; 
				Input::GetInput().SetPlatform(platform);
			};

			inline void SetPlatform(std::string platform) {


				if (platform == "WINDOWS") {
					_platform = PLATFORM::WINDOWS;
				}
				else if (platform == "GLFW") {
					_platform = PLATFORM::GLFW;
				}
				else if (platform == "LINUX") {
					_platform = PLATFORM::LINUX;
				}
				else if (platform == "MAC") {
					_platform = PLATFORM::MAC;
				}

				Input::GetInput().SetPlatform(_platform);
			};

			inline void SetRenderEngine(RenderEngines engine) { _engine = engine; };

			inline void SetRenderEngine(std::string engine) { 

				if (engine == "OpenGL") {
					_engine = RenderEngines::OpenGL;
				}
				else if (engine == "DirectX") {
					_engine = RenderEngines::DirectX;
				}
			};

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
			void AddChar(unsigned int c, bool UTF16 = false);

			void TestFunction();

			void AddShaderDef(std::shared_ptr<ShaderDef> _def);


			static Camera2D* Cam() { return get().current_cam; }
			static void SetCam(Camera2D* new_cam) { 
				get().current_cam = new_cam; 
			}

			static FileManager* FileMgr() { return &get()._file_manager; }

			static cErrorLogger* Log() { return get().log; }

			static World* getWorld() { return &(get().w); }

			static EntityManager* EntityMgr() {	return getWorld()->EntityMgr(); }

			static StateMachine& state() { return get().GameFSM; }

			static GUIPlatform& getGUI() { return get()._gui->Get(); }

			static ShaderManager& getShader() {	return get().shader_mgr; }

			static Shader& getCurrentShader() { return get().shader_mgr.Get(); }
			static bool hasCurrentShader() { return get().shader_mgr.isSet(); }

			static RenderEngineBase& getRenderer() { return get().renderer.Get(); }

			static Context& getContext() { return get().ctx; }

			static EventManager& Events() {	return EventManager::Instance(); }

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