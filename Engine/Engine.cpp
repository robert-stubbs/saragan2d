#include "EnginePCH.h"
#include "Engine.h"

namespace GameEngine {

	Engine::~Engine()
	{

	}

	void Engine::SetAssetDir(std::string directory)
	{
		asset_dir = directory;
	}

	void Engine::SetWindowName(std::string name)
	{
		WindowName = name;
	}

	void Engine::SetWindowSize(int width, int height, bool isFullScreen)
	{
		WindowWidth = width;
		WindowHeight = height;
		fullscreen = isFullScreen;
	}

	bool Engine::PreInit()
	{
		/* Initialize the library */
		if (!glfwInit()) {
			return false;
		}

		if (fullscreen) {
			window = glfwCreateWindow(WindowWidth, WindowHeight, WindowName.c_str(), glfwGetPrimaryMonitor(), NULL);
		}
		else {
			/* Create a windowed mode window and its OpenGL context */
			window = glfwCreateWindow(WindowWidth, WindowHeight, WindowName.c_str(), NULL, NULL);
		}

		if (!window)
		{
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);

		renderer = Renderer(RenderEngines::OpenGL);
		shader_mgr = ShaderManager(RenderEngines::OpenGL);
		return true;
	}

	bool Engine::Init()
	{		
		getRenderer().Init();
		return true;
	}

	bool Engine::PostInit()
	{
		getRenderer().PostInit();
		return true;
	}

	bool Engine::Update(float DeltaTime)
	{
		Update3D(DeltaTime);
		UpdateOrth(DeltaTime);
		return true;
	}

	bool Engine::Update3D(float DeltaTime)
	{

		return true;
	}

	bool Engine::UpdateOrth(float DeltaTime)
	{

		return true;
	}

	void Engine::Render()
	{
		getRenderer().RenderStart();

		Render3D();
		RenderOrth();
	}

	void Engine::Render3D()
	{

	}

	void Engine::RenderOrth()
	{

	}

	void Engine::RenderEnd()
	{
		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	bool Engine::Cleanup()
	{
		getRenderer().Cleanup();

		glfwTerminate();
		return true;
	}

}