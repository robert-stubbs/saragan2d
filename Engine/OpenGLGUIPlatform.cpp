#include "EnginePCH.h"
#include "OpenGLGUIPlatform.h"
#include "Types.h"
#include "Engine.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "backends/imgui_impl_opengl3.cpp"
#include "examples/imgui_impl_glfw.cpp"

namespace GameEngine
{
    OpenGLGUIPlatform::~OpenGLGUIPlatform()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

	void OpenGLGUIPlatform::Init()
	{
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        

        GLFWwindow* window = (GLFWwindow*)Engine::get().getContext().Get().GetWindowHandle();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 440");
	}

    void OpenGLGUIPlatform::DemoTest()
    {
        static bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);
    }


    void OpenGLGUIPlatform::NewScene(float dt)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.DeltaTime = dt;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowSize(io.DisplaySize);
    }

    void OpenGLGUIPlatform::EndAndRender()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)Engine::get().WindowWidth, (float)Engine::get().WindowHeight);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void OpenGLGUIPlatform::Begin(std::string name)
    {
        ImGui::Begin(name.c_str());
    }

    void OpenGLGUIPlatform::End()
    {
        ImGui::End();
    }

    void OpenGLGUIPlatform::BeginChild(std::string name)
    {
        ImGui::BeginChild(name.c_str());
    }

    void OpenGLGUIPlatform::EndChild()
    {
        ImGui::EndChild();
    }

    void OpenGLGUIPlatform::ResizeWindow(int width, int height)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)Engine::get().WindowWidth, (float)Engine::get().WindowHeight);
    }

    void OpenGLGUIPlatform::KeyDown(int Key)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[Key] = true;
    }

    void OpenGLGUIPlatform::KeyUp(int Key)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[Key] = false;
    }

    void OpenGLGUIPlatform::MouseDown(int button)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[button] = true;
    }

    void OpenGLGUIPlatform::MouseUp(int button)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[button] = false;
    }

    void OpenGLGUIPlatform::MouseMove(float x, float y)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(x, y);
    }

    void OpenGLGUIPlatform::AddChar(unsigned int c, bool UTF16)
    {
        ImGuiIO& io = ImGui::GetIO();

        if (UTF16) {
            io.AddInputCharacterUTF16((unsigned short)c);
        }
        else {
            io.AddInputCharacter(c);
        }
    }
}