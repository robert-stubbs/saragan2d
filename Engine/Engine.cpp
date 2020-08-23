#include "EnginePCH.h"
#include "Engine.h"
#include "EventManager.h"
#include "Default2DShader.h"

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
		cam = new Camera2D(800, 600);
	}

	void Engine::SetWindowSize(int width, int height, bool isFullScreen)
	{
		WindowWidth = width;
		WindowHeight = height;
		fullscreen = isFullScreen;
	}

	void Engine::TestFunction()
	{
		std::cout << "Test Called" << std::endl; 
	}

	bool Engine::PreInit()
	{
		ctx.SetPlatform(_platform);
		if (ctx.InitWindow(WindowWidth, WindowHeight, WindowName, fullscreen))
		{
			renderer = Renderer(_engine);

			ctx.InitContext();

			shader_mgr = ShaderManager(_engine);

			//System = new SystemManager();
			//EntityMgr = new EntityManager();

			//glfwSetKeyCallback(window, key_callback);


			//System->Init();

			std::string asset_dir = "C:/Assets/";
			std::string ft = asset_dir + "Font/Vera.ttf";
			//font = new Font(30, ft.c_str());

			//GameFSM = new StateMachine();
			return true;
		}

		return false;
	}

	bool Engine::Init()
	{		
		AddShaderDef(
			std::make_shared<Default2DShader>(
				Default2DShader(
					Engine::get().asset_dir + "Shaders/VertexShader.glsl",
					Engine::get().asset_dir + "Shaders/FragmentShader.glsl"
				)
			)
		);

		for (std::shared_ptr<ShaderDef>& def : _shader_definitions)
		{
			def->SetupShader();
		}

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
		cam->Update(DeltaTime);

		//System->Update(DeltaTime);
		///GameFSM->Update(DeltaTime);



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
		getContext().SwapContextBuffers();
	}

	bool Engine::Cleanup()
	{
		getRenderer().Cleanup();

		return true;
	}

	void Engine::AddShaderDef(std::shared_ptr<ShaderDef> _def)
	{
		_shader_definitions.push_back(_def);
	}
	
	
	void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (Input::Get().IsKeyPressed(ENGINE_KEY_A)) {
			Engine::get().cam->dx = 10;
		}
		else {
			if (Input::Get().IsKeyReleased(ENGINE_KEY_D))
			{
				Engine::get().cam->dx = 0;
			}			
		}

		if (Input::Get().IsKeyPressed(ENGINE_KEY_D)) {
			Engine::get().cam->dx = -10;
		}
		else {
			if (Input::Get().IsKeyReleased(ENGINE_KEY_A))
			{
				Engine::get().cam->dx = 0;
			}
		}

		if (Input::Get().IsKeyPressed(ENGINE_KEY_W)) {
			Engine::get().cam->dy = 10;
		}
		else {
			if (Input::Get().IsKeyReleased(ENGINE_KEY_S))
			{
				Engine::get().cam->dy = 0;
			}
		}

		if (Input::Get().IsKeyPressed(ENGINE_KEY_S)) {
			Engine::get().cam->dy = -10;
		}
		else {
			if (Input::Get().IsKeyReleased(ENGINE_KEY_W))
			{
				Engine::get().cam->dy = 0;
			}
		}
	}
}