#include "pch.h"
#include "LibLoader.h"

#ifdef WIN32
	#include <windows.h>
#endif

namespace Crank
{

	bool LibLoader::LoadWindowAPI(WindowAPIs api)
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
		default:
			return false;
		}
		

		CREATEWINDOWAPI _CreateWindowAPI = 0;

		// function pointer to dll's 'CreateRenderDevice' function
		_CreateWindowAPI = (CREATEWINDOWAPI)GetProcAddress((HMODULE)m_WindowDLL, "CreateWindowAPI");

		if (!_CreateWindowAPI)
			return false;

		// call dll's create function
		if (!_CreateWindowAPI(&m_Window))
		{
			m_Window = nullptr;
			return false;
		}

		return true;
	}

	void LibLoader::ReleaseWindowAPI()
	{
		RELEASEWINDOWAPI _ReleaseWindowAPI = 0;

		if (m_WindowDLL)
		{
			// function pointer to dll 'ReleaseRenderDevice' function
			_ReleaseWindowAPI = (RELEASEWINDOWAPI)GetProcAddress((HMODULE)m_WindowDLL, "ReleaseWindowAPI");
		}
		// call dll's release function
		if (m_Window)
		{
			if (!_ReleaseWindowAPI(&m_Window))
			{
				m_Window = nullptr;
			}
		}
		
		//FreeLibrary((HMODULE)m_WindowDLL);
		//m_WindowDLL = nullptr;
	}

	bool LibLoader::LoadRendererAPI(RendererAPIs api)
	{
		// decide which API should be used
		switch (api)
		{
		case RendererAPIs::OpenGL:
			m_RendererAPIDLL = LoadLibrary(L"OpenGL.dll");
			if (!m_RendererAPIDLL)
				return false;
			break;
		default:
			return false;
		}


		CREATERENDERERAPI _CreateRenderAPI = 0;

		// function pointer to dll's 'CreateRenderDevice' function
		_CreateRenderAPI = (CREATERENDERERAPI)GetProcAddress((HMODULE)m_RendererAPIDLL, "CreateRendererAPI");

		if (!_CreateRenderAPI)
			return false;

		// call dll's create function
		if (!_CreateRenderAPI(&m_RendererAPI))
		{
			m_RendererAPI = nullptr;
			return false;
		}

		return true;
	}

	void LibLoader::ReleaseRendererAPI()
	{
		RELEASERENDERERAPI _ReleaseRendererAPI = 0;

		if (m_RendererAPIDLL)
		{
			// function pointer to dll 'ReleaseRenderDevice' function
			_ReleaseRendererAPI = (RELEASERENDERERAPI)GetProcAddress((HMODULE)m_RendererAPIDLL, "ReleaseRendererAPI");
		}
		// call dll's release function
		if (m_RendererAPI)
		{
			if (!_ReleaseRendererAPI(&m_RendererAPI))
			{
				m_RendererAPI = nullptr;
			}
		}
		FreeLibrary((HMODULE)m_RendererAPIDLL);
	}

}