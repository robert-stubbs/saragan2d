#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Renderer.h"

namespace GameEngine {

	class Engine
	{
		private:
			Engine() {};

			std::string asset_dir;

			Renderer renderer;
		public:
			~Engine();

			bool fullscreen = false;

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
			bool Cleanup();

			static Engine& get() {
				//instantiate the engine
				static Engine instance;
				//return static instance
				return instance;
			}
		
	};
}

#endif