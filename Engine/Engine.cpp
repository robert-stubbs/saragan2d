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
	}

	void Engine::SetWindowSize(int width, int height, bool isFullScreen)
	{
		WindowWidth = width;
		WindowHeight = height;
		fullscreen = isFullScreen;
		cam = new Camera2D((float)width, (float)height);
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



			//System->Init();

			std::string asset_dir = "C:/Assets/";
			std::string ft = asset_dir + "Font/Vera.ttf";
			//font = new Font(30, ft.c_str());

			GameFSM = StateMachine();
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
		

		GameFSM.Update(DeltaTime);
		GameFSM.UpdateOrth(DeltaTime);

		return true;
	}

	void Engine::Render()
	{
		getRenderer().RenderStart();

		GameFSM.Render();
		GameFSM.RenderOrth();

		getContext().SwapContextBuffers();
	}

	bool Engine::Cleanup()
	{
		getRenderer().Cleanup();

		return true;
	}

	void Engine::KeyDown(int Key)
	{
		GameFSM.KeyDown(Key);
	}

	void Engine::KeyUp(int Key)
	{
		GameFSM.KeyUp(Key);
	}

	void Engine::MouseDown(int button)
	{
		GameFSM.MouseDown(button);
	}

	void Engine::MouseUp(int button)
	{
		GameFSM.MouseUp(button);
	}

	void Engine::MouseMove(float x, float y)
	{
		GameFSM.MouseMove(x,y);
	}

	void Engine::AddShaderDef(std::shared_ptr<ShaderDef> _def)
	{
		_shader_definitions.push_back(_def);
	}
	
	
}