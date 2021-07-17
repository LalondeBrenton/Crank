#pragma once
#include "pch.h"
#include "Application.h"

#include "Crank/Events/KeyEvent.h"

#include <imgui.h>

namespace Crank
{

	Application* Application::s_Instance;

	Application::Application(ApplicationCommandLineArgs args, const std::string& name)
		: m_CommandLineArgs(args), m_Name(name)
	{
		s_Instance = this;

		m_RendererAPI = RendererAPI::Create(RendererAPIs::OpenGL);

		m_Window = Window::Create(m_WindowAPI);

		m_Window->Init(WindowProperties(m_Name), m_RendererAPI);
		m_Window->SetEventCallback(CGE_BIND_EVENT_FN(Application::OnEvent));

		m_RendererAPI->SetClearColor(glm::vec4(0.8f, 0.2f, 0.25f, 1.0f));

		m_ImGuiLayer = m_RendererAPI->CreateImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(CGE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(CGE_BIND_EVENT_FN(Application::OnWindowResize));


		if (e.GetEventType() == Crank::EventType::KeyReleased)
		{
			KeyReleasedEvent keyevent = dynamic_cast<KeyReleasedEvent&>(e);
			if (keyevent.GetKeyCode() == Key::F1)
			{
				m_SwapWindowAPI = true;
			}
		}

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
			m_RendererAPI->Clear();

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();

			}


			m_Window->SwapBuffers();

			if (m_SwapWindowAPI)
			{
				if (m_WindowAPI == WindowAPIs::WindowAPIGLFW)
					m_WindowAPI = WindowAPIs::WindowAPIWIN32;
				else
					m_WindowAPI = WindowAPIs::WindowAPIGLFW;
				
				m_LayerStack.PopOverlay(m_ImGuiLayer);
				m_Window = nullptr;
				m_Window = Window::Create(m_WindowAPI);

				m_Window->Init(WindowProperties(m_Name), m_RendererAPI);
				m_Window->SetEventCallback(CGE_BIND_EVENT_FN(Application::OnEvent));
				m_RendererAPI->SetClearColor(glm::vec4(0.8f, 0.2f, 0.25f, 1.0f));

				m_ImGuiLayer = m_RendererAPI->CreateImGuiLayer();
				PushOverlay(m_ImGuiLayer);

				m_SwapWindowAPI = false;
			}
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}