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

		if (m_Window->GetAPI() == WindowAPIs::WindowAPIGLFW)
		{
			CGE_CORE_INFO("Loading OpenGL with glad and GLFW");
			if (!gladLoadGLLoader((GLADloadproc)m_Window->GetProcAddress()))
			{
				__debugbreak();
			}
		}
		else
		{
			CGE_CORE_INFO("Loading OpenGL with glad and its loader");
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