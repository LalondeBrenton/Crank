#pragma once
#include "Base/Base.h"
#include "Base/LibLoader.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Window/Window.h"

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

		static Application& Get() { return *s_Instance; }
		Ref<Window> GetWindow() { return m_Window; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

		void Run();
	private:
		static Application* s_Instance;
		ApplicationCommandLineArgs m_CommandLineArgs;
		LibLoader m_LibLoader;

		Ref<RendererAPI> m_RendererAPI;
		Ref<Window> m_Window;

		std::string m_Name;
		WindowAPIs m_WindowAPI = WindowAPIs::WindowAPIGLFW;

		bool m_Running = true;
		bool m_Minimized = false;

		bool m_SwapWindowAPI = false;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);
}