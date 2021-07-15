#pragma once

#include "Window/Window.h"
#include "Renderer/RendererAPI.h"

#include <string>

namespace Crank
{
	class LibLoader
	{
	public:
		LibLoader() : m_WindowDLL(nullptr), m_Window(nullptr), m_RendererAPIDLL(nullptr), m_RendererAPI(nullptr)
		{}
		~LibLoader() {}

		bool LoadWindowAPI(WindowAPIs api);
		void ReleaseWindowAPI();
		Window* GetWindowAPI() { return m_Window; }

		bool LoadRendererAPI(RendererAPIs api);
		void ReleaseRendererAPI();
		RendererAPI* GetRendererAPI() { return m_RendererAPI; }

	private:
		void* m_WindowDLL;
		Window* m_Window;

		void* m_RendererAPIDLL;
		RendererAPI* m_RendererAPI;
	};

}