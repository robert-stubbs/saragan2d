#include "EnginePCH.h"
#include "OpenGLGUIPlatform.h"
#include "Types.h"
#include "Engine.h"

#include "imgui_impl_opengl3.h"


namespace GameEngine
{
    OpenGLGUIPlatform::~OpenGLGUIPlatform()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

	void OpenGLGUIPlatform::Init()
	{
        ImGui::CreateContext();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)       

        io.KeyMap[ImGuiKey_Tab] = ENGINE_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = ENGINE_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = ENGINE_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = ENGINE_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = ENGINE_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = ENGINE_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = ENGINE_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = ENGINE_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = ENGINE_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = ENGINE_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = ENGINE_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = ENGINE_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = ENGINE_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = ENGINE_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = ENGINE_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = ENGINE_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = ENGINE_KEY_A;
        io.KeyMap[ImGuiKey_C] = ENGINE_KEY_C;
        io.KeyMap[ImGuiKey_V] = ENGINE_KEY_V;
        io.KeyMap[ImGuiKey_X] = ENGINE_KEY_X;
        io.KeyMap[ImGuiKey_Y] = ENGINE_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = ENGINE_KEY_Z;


        ImGui_ImplOpenGL3_Init("#version 440");

        ImFont* f = io.Fonts->AddFontDefault();
        ImGui_ImplOpenGL3_CreateFontsTexture();

        io.DisplaySize = ImVec2((float)Engine::get().WindowWidth, (float)Engine::get().WindowHeight);
        

	}

    void OpenGLGUIPlatform::DemoTest(float dt)
    {
        static bool show_demo_window = true;
        ImGuiIO& io = ImGui::GetIO();

        io.DeltaTime = dt;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }
}