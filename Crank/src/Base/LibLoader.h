#pragma once

#include "Interfaces/Window.h"

#include <string>

namespace Crank
{
	enum class WindowAPIs
	{
		WindowAPIGLFW, 
		WindowAPIWIN32
	};

	class LibLoader
	{
	public:
		LibLoader() : m_WindowDLL(nullptr), m_Window(nullptr) {}
		~LibLoader() {}

		bool LoadWindow(WindowAPIs api);
		void ReleaseWindow();
		Window* GetWindow() { return m_Window; }

	private:
		void* m_WindowDLL;
		Window* m_Window;
	};

}