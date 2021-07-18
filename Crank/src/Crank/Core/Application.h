#pragma once
#include "Crank/Base/Base.h"
#include "Crank/Core/LayerStack.h"
#include "Crank/Events/Event.h"
#include "Crank/Events/ApplicationEvent.h"

#include "Crank/Window/Window.h"

namespace Crank
{
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			CGE_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	class Application
	{
	public:
		Application(ApplicationCommandLineArgs args = ApplicationCommandLineArgs(), const std::string& name = "Crank Graphics Engine");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void Run();
		void Close();

		static Application& Get() { return *s_Instance; }
		Ref<Window> GetWindow() { return m_Window; }
		Ref<RendererAPI> GetRenderAPI() { return m_RendererAPI; }

		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

	private:
		static Application* s_Instance;

		ApplicationCommandLineArgs m_CommandLineArgs;
		Ref<RendererAPI> m_RendererAPI;
		Ref<Window> m_Window;
		std::string m_Name;
		WindowAPIs m_WindowAPI;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		ImGuiLayer* m_ImGuiLayer;

		bool m_SwapWindowAPI = false;
	};

	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);
}