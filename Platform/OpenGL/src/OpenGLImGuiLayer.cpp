#include "OpenGLImGuiLayer.h"

#include "Core/Application.h"

//#include <imgui.h>
#ifdef WIN32
//#include <backends/imgui_impl_win32.h>
#endif
//#include <backends/imgui_impl_glfw.h>
//#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Crank
{

	OpenGLImGuiLayer::OpenGLImGuiLayer()
	{

	}

	void OpenGLImGuiLayer::OnAttach()
	{
		//// Setup Dear ImGui context
		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		////io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		////io.ConfigViewportsNoAutoMerge = true;
		////io.ConfigViewportsNoTaskBarIcon = true;

		//// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		////ImGui::StyleColorsClassic();

		//// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		//ImGuiStyle& style = ImGui::GetStyle();
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	style.WindowRounding = 0.0f;
		//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		//}

		//// Setup Platform/Renderer backends
		//ImGui_ImplGlfw_InitForOpenGL(window, true);
		//ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void OpenGLImGuiLayer::OnDetach()
	{

	}

	void OpenGLImGuiLayer::OnEvent(Event& e)
	{

	}

	void OpenGLImGuiLayer::Begin()
	{

	}

	void OpenGLImGuiLayer::End()
	{

	}

}