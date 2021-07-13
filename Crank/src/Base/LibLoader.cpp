#include "pch.h"
#include "LibLoader.h"

#ifdef WIN32
	#include <windows.h>
#endif

namespace Crank
{

	bool LibLoader::LoadWindow(WindowAPIs api)
	{

		// decide which API should be used
		switch (api)
		{
		case WindowAPIs::WindowAPIGLFW:
			m_WindowDLL = LoadLibrary(L"GLFWWindow.dll");
			if (!m_WindowDLL)
				return false;
			break;
		case WindowAPIs::WindowAPIWIN32:
			m_WindowDLL = LoadLibrary(L"Win32Window.dll");
			if (!m_WindowDLL)
				return false;
			break;
		}
		

		CREATEWINDOWAPI _CreateRenderDevice = 0;

		// function pointer to dll's 'CreateRenderDevice' function
		_CreateRenderDevice = (CREATEWINDOWAPI)GetProcAddress((HMODULE)m_WindowDLL, "CreateWindowAPI");

		if (!_CreateRenderDevice)
			return false;

		// call dll's create function
		if (!_CreateRenderDevice(&m_Window))
		{
			m_Window = nullptr;
			return false;
		}

		return true;
	}

	void LibLoader::ReleaseWindow()
	{
		RELEASEWINDOWAPI _ReleaseRenderDevice = 0;

		if (m_WindowDLL)
		{
			// function pointer to dll 'ReleaseRenderDevice' function
			_ReleaseRenderDevice = (RELEASEWINDOWAPI)GetProcAddress((HMODULE)m_WindowDLL, "ReleaseWindowAPI");
		}
		// call dll's release function
		if (m_Window)
		{
			if (!_ReleaseRenderDevice(&m_Window))
			{
				m_Window = nullptr;
			}
		}
	}
}