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
		current_dt = 0;

		ctx.SetPlatform(_platform);
		if (ctx.InitWindow(WindowWidth, WindowHeight, WindowName, fullscreen))
		{
			renderer = Renderer(_engine);

			ctx.InitContext();

			shader_mgr = ShaderManager(_engine);

			// Load the font engine
			Font::GetFont() = Font(_engine);
			std::string asset_dir = "C:/Assets/";
			std::string ft = asset_dir + "Font/Vera.ttf";
			Font::Get().LoadFont(ft, 30);

			//System = new SystemManager();
			//EntityMgr = new EntityManager();

			_gui = new GUI(RenderEngines::OpenGL);

			//System->Init();

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

		_gui->Get().Init();

		loaded = true;

		return true;
	}

	bool Engine::PostInit()
	{
		getRenderer().PostInit();

		return true;
	}

	bool Engine::Update(float DeltaTime)
	{
		current_dt = DeltaTime;
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

		GUI::Get().DemoTest(current_dt > 0 ? current_dt : 1.0f/60.0f);

		getContext().SwapContextBuffers();
	}

	bool Engine::Cleanup()
	{
		getRenderer().Cleanup();

		return true;
	}

	void Engine::KeyDown(int Key)
	{
		getGUI().KeyDown(Key);

		if (!ImGui::IsAnyWindowFocused() && !ImGui::IsAnyItemFocused()) {
			GameFSM.KeyDown(Key);
		}
	}

	void Engine::KeyUp(int Key)
	{
		getGUI().KeyUp(Key);
		if (!ImGui::IsAnyWindowFocused() && !ImGui::IsAnyItemFocused()) {
			GameFSM.KeyUp(Key);
		}
	}

	void Engine::MouseDown(int button)
	{
		getGUI().MouseDown(button);
		GameFSM.MouseDown(button);
	}

	void Engine::MouseUp(int button)
	{
		getGUI().MouseUp(button);
		GameFSM.MouseUp(button);
	}

	void Engine::MouseMove(float x, float y)
	{
		getGUI().MouseMove(x,y);
		GameFSM.MouseMove(x,y);
	}

	void Engine::AddChar(unsigned int c, bool UTF16)
	{
		getGUI().AddChar(c, UTF16);
	}

	void Engine::AddShaderDef(std::shared_ptr<ShaderDef> _def)
	{
		_shader_definitions.push_back(_def);
	}
	
	
}