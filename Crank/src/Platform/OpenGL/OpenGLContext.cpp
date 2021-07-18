#include "pch.h"
#include "OpenGLContext.h"

#include "Crank/Window/Window.h"
#include "Crank/Core/Application.h"

#include <glad/glad.h>

namespace Crank
{

	bool OpenGLContext::GladInit = false;

	OpenGLContext::OpenGLContext()
	{

	}

	OpenGLContext::~OpenGLContext()
	{

	}

	void OpenGLContext::Init()
	{

		if (GladInit)
			return;

		if (Application::Get().GetWindow().get()->GetAPI() == WindowAPIs::WindowAPIGLFW)
		{
			CGE_CORE_INFO("Loading OpenGL with glad and GLFW");
			if (!gladLoadGLLoader((GLADloadproc)Application::Get().GetWindow().get()->GetProcAddress()))
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
		GladInit = true;
	}

	void OpenGLContext::SwapBuffers()
	{
		Application::Get().GetWindow().get()->SwapBuffers();
	}
}