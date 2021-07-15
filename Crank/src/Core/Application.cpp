#pragma once
#include "pch.h"
#include "Application.h"

#include "Events/KeyEvent.h"

namespace Crank
{
	Application::Application(ApplicationCommandLineArgs args, const std::string& name)
		: m_CommandLineArgs(args), m_Name(name)
	{
		m_LibLoader.LoadRendererAPI(RendererAPIs::OpenGL);
		m_RendererAPI = m_LibLoader.GetRendererAPI();

		m_LibLoader.LoadWindowAPI(m_WindowAPI);
		m_Window = m_LibLoader.GetWindowAPI();

		m_Window->Init(WindowProperties(m_Name), m_RendererAPI);
		m_Window->SetEventCallback(CGE_BIND_EVENT_FN(Application::OnEvent));
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
			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();

			}

			m_Window->OnUpdate();
			m_Window->SwapBuffers();

			if (m_SwapWindowAPI)
			{
				if (m_WindowAPI == WindowAPIs::WindowAPIGLFW)
					m_WindowAPI = WindowAPIs::WindowAPIWIN32;
				else
					m_WindowAPI = WindowAPIs::WindowAPIGLFW;

				m_LibLoader.ReleaseWindowAPI();

				m_LibLoader.LoadWindowAPI(m_WindowAPI);
				m_Window = m_LibLoader.GetWindowAPI();

				m_Window->Init(WindowProperties(m_Name), m_RendererAPI);
				m_Window->SetEventCallback(CGE_BIND_EVENT_FN(Application::OnEvent));
				m_SwapWindowAPI = false;
			}
		}
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