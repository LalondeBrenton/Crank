#include "pch.h"
#include "Window.h"

#include "Platform/GLFWWindow/GLFWWindow.h"

#ifdef WIN32
#include "Platform/Win32Window/Win32Window.h"
#endif

namespace Crank
{

	Ref<Window> Window::Create(WindowAPIs api)
	{
		if (api == WindowAPIs::WindowAPIWIN32)
			return CreateRef<Win32Window>();
		return CreateRef<GLFWWindow>();
	}

}