#pragma once

#include "Crank/Window/Window.h"
#include "Crank/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>
#include "GLFWImGuiImpl.h"

namespace Crank
{

	class GLFWWindow : public Window
	{
	public:
		GLFWWindow();
		virtual ~GLFWWindow();

		virtual WindowAPIs GetAPI() override { return WindowAPIs::WindowAPIGLFW; }

		virtual void Init(const WindowProperties& props, Ref<RendererAPI> rendererapi);

		void OnUpdate() override;

		void SwapBuffers() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }
		virtual void* GetProcAddress() const override { return glfwGetProcAddress; }

		virtual bool ImGuiInit() override { return ImGui_ImplGlfw_InitForOpenGL(m_Window, true); }
		virtual void ImGuiNewFrame() override { ImGui_ImplGlfw_NewFrame(); }
		virtual void ImGuiShutdown() override { ImGui_ImplGlfw_Shutdown(); }
		virtual void MakeCurrentRenderContext() { glfwMakeContextCurrent(m_Window); }
	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		virtual void Shutdown();

		WindowData m_Data;
		GLFWwindow* m_Window;
		Ref<RendererAPI> m_RendererAPI;
		Ref<GraphicsContext> m_RenderContext;
	};

}