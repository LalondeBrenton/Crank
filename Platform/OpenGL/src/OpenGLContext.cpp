#include "OpenGLContext.h"
#include "Window/Window.h"

#include <glad/glad.h>

namespace Crank
{

	OpenGLContext::OpenGLContext()
	{

	}

	OpenGLContext::~OpenGLContext()
	{

	}

	void OpenGLContext::Init(Window* window)
	{
		m_Window = window;

		// Init Glad Here
		if (m_Window->GetAPI() == WindowAPIs::WindowAPIGLFW)
		{
			if (!gladLoadGLLoader((GLADloadproc)m_Window->GetProcAddress()))
			{
				__debugbreak();
			}
		}
		else
		{
			if (!gladLoadGL())
			{
				__debugbreak();
			}
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		if (m_Window->GetAPI() == WindowAPIs::WindowAPIGLFW)
			m_Window->SwapBuffers();
		::SwapBuffers(GetDC((HWND)m_Window->GetNativeWindow()));
	}
}