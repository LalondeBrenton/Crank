#include "pch.h"
#include "Win32Window.h"

#include "Crank/Core/Application.h"

#include "Crank/Events/ApplicationEvent.h"
#include "Crank/Events/KeyEvent.h"
#include "Crank/Events/MouseEvent.h"

#include "Crank/Core/KeyCodes.h"


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <windowsx.h>
#include <winuser.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Crank
{
	// function prototypes and pointers
	typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC) (void);
	typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int interval);
	typedef int (WINAPI* PFNWGLGETSWAPINTERVALEXTPROC) (void);
	PFNWGLSWAPINTERVALEXTPROC			wglSwapIntervalEXT;
	PFNWGLGETSWAPINTERVALEXTPROC		wglGetSwapIntervalEXT;
	PFNWGLGETEXTENSIONSSTRINGEXTPROC	wglGetExtensionsStringEXT;

	static LPCWSTR s_myclass = L"myclass";

	Win32Window::Win32Window()
		: m_Data(), m_Window(nullptr), m_DC(0), m_RC(0), m_RendererAPI(nullptr), m_RenderContext(nullptr)
	{
		if (!Log::IsInitalized())
			Log::Init();
	}

	Win32Window::~Win32Window()
	{
		Shutdown();
	}

	void Win32Window::Init(const WindowProperties& props, Ref<RendererAPI> rendererapi)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		m_RendererAPI = rendererapi;

		m_RenderContext = m_RendererAPI->GetContext();

		CGE_CORE_INFO("Creating Win32 window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		//WNDCLASS wc = { 0 };
		//wc.lpfnWndProc = WindowProcedure;
		//wc.hInstance = GetModuleHandle(0);
		//wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
		//wc.lpszClassName = s_myclass;
		//wc.style = CS_OWNDC;

		//ATOM result = RegisterClass(&wc);

		//if (!result) LastErrormsg();
		//CGE_CORE_ASSERT(result, "Could not register Window class!");

		std::wstring wtitle = ConvertStringtoW(props.Title);
		LPCWSTR title = wtitle.c_str();

		//m_Window = CreateWindowEx(0, s_myclass, (LPCWSTR)title,
		//	WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		//	props.Width, props.Height, 0, 0, GetModuleHandle(0), 0);


		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProcedure, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, s_myclass, NULL };
		::RegisterClassEx(&wc);
		m_Window = ::CreateWindow(wc.lpszClassName, title, WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);
	

		if (!m_Window) LastErrormsg();
		CGE_CORE_ASSERT(m_Window, "Could not create the Window!");

		// Set the Window data pointer
		LONG_PTR lpthis = SetWindowLongPtr(m_Window, GWLP_USERDATA, (LONG_PTR)this);

		ShowWindow(m_Window, SW_SHOWDEFAULT);
		UpdateWindow(m_Window);
		SetFocus(m_Window);

		// Create a Render Context
		if (m_RendererAPI->GetAPI() == RendererAPIs::OpenGL)
		{
			CreateOpenGLContext();

			// Get Pointers for swap intervals if available
			if (WGLExtensionSupported("WGL_EXT_swap_control"))
			{
				wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
				wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
				wglSwapIntervalEXT(1);
			}
		}
		
		// Init RenderContext
		m_RenderContext->Init();
	}

	void Win32Window::OnUpdate()
	{
		MSG msg;
		while (PeekMessage(&msg, m_Window, 0, 0, PM_REMOVE) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Win32Window::SwapBuffers()
	{

		if (Application::Get().GetRenderAPI()->GetAPI() == RendererAPIs::OpenGL)
			::SwapBuffers(m_DC);
		else
			Application::Get().GetRenderAPI()->GetContext()->SwapBuffers();

	}

	void Win32Window::SetVSync(bool enabled)
	{
		// Set the vsync interval
		if (Application::Get().GetRenderAPI()->GetAPI() == RendererAPIs::OpenGL)
		{
			if (enabled)
				wglSwapIntervalEXT(1);
			else
				wglSwapIntervalEXT(0);
			m_Data.VSync = enabled;
		}
	}

	bool Win32Window::IsVSync() const
	{
		return m_Data.VSync;
	}

	void Win32Window::Shutdown()
	{
		if (m_RendererAPI->GetAPI() == RendererAPIs::OpenGL)
		{
			if (!wglMakeCurrent(NULL, NULL))                 // Are We Able To Release The DC And RC Contexts?
				LastErrormsg();
			if (!wglDeleteContext(m_RC))                 // Are We Able To Delete The RC?
			{
				LastErrormsg();
				m_RC = NULL;                           // Set DC To NULL
			}
			if (m_DC && !ReleaseDC(m_Window, m_DC))                    // Are We Able To Release The DC
			{
				LastErrormsg();
				m_DC = NULL;                           // Set DC To NULL
			}
		}
		if (m_Window && !DestroyWindow(m_Window))                   // Are We Able To Destroy The Window?
		{
			LastErrormsg();
			m_Window = NULL;                          // Set hWnd To NULL
		}
		if (!UnregisterClass(s_myclass, GetModuleHandle(0)))               // Are We Able To Unregister Class
		{
			LastErrormsg();
		}
	}

	LRESULT __stdcall Win32Window::WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
	{
		LONG_PTR lpUserData = GetWindowLongPtr(window, GWLP_USERDATA);
		Win32Window* objwindow = (Win32Window*)lpUserData;

		// ImGui MSG handler
		if (ImGui_ImplWin32_WndProcHandler(window, msg, wp, lp))
			return 0;

		switch (msg)
		{
		case WM_CLOSE:
		{
			WindowCloseEvent event;
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			PostQuitMessage(0);
			return 0;
		}
		case WM_SIZE:
		{
			objwindow->m_Data.Width = LOWORD(lp);
			objwindow->m_Data.Height = HIWORD(lp);
			WindowResizeEvent event(objwindow->m_Data.Width, objwindow->m_Data.Height);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_ACTIVATE: // Has Focus?
		{
			bool isactive = (bool)wp;

			break;
		}
		// key was pressed
		case WM_KEYDOWN:
		{
			KeyCode key = WinToKeyCode(wp);
			bool isBitSet = lp & (1 << 30);
			KeyPressedEvent event(key, (isBitSet == false) ? 0 : 1);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_KEYUP:
		{
			KeyCode key = WinToKeyCode(wp);
			KeyReleasedEvent event(key);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_CHAR:
		{
			KeyTypedEvent event((KeyCode)wp);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			float x = (float)GET_X_LPARAM(lp);
			float y = (float)GET_Y_LPARAM(lp);
			MouseMovedEvent event(x, y);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_MOUSEWHEEL:
		{
			short scroll = GET_WHEEL_DELTA_WPARAM(wp);
			MouseScrolledEvent event(0.0f, (float)scroll / 120.0f);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			MouseButtonPressedEvent event(Mouse::ButtonLeft);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			MouseButtonPressedEvent event(Mouse::ButtonMiddle);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			MouseButtonPressedEvent event(Mouse::ButtonRight);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			MouseButtonReleasedEvent event(Mouse::ButtonLeft);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			MouseButtonReleasedEvent event(Mouse::ButtonMiddle);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			MouseButtonReleasedEvent event(Mouse::ButtonRight);
			if (objwindow->m_Data.EventCallback)
				objwindow->m_Data.EventCallback(event);
			return 0;
		}
		}

		return DefWindowProc(window, msg, wp, lp);
	}

	void Win32Window::LastErrormsg()
	{
		//Get the error message ID, if any.
		DWORD errorMessageID = ::GetLastError();

		LPSTR messageBuffer = nullptr;

		//Ask Win32 to give us the string version of that message ID.
		//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		//Copy the error message into a std::string.
		std::string message(messageBuffer, size);

		//Free the Win32's string's buffer.
		LocalFree(messageBuffer);

		MessageBox(m_Window, ConvertStringtoW(message).c_str(), L"Last Error", 0);
	}

	std::wstring Win32Window::ConvertStringtoW(const std::string& text)
	{
		std::wstring temp(text.length(), L' ');
		std::copy(text.begin(), text.end(), temp.begin());
		return (LPCWSTR)temp.c_str();
	}

	KeyCode Win32Window::WinToKeyCode(WPARAM wp)
	{
		switch (wp)
		{
		case VK_BACK:
			return Key::Backspace;
		case VK_TAB:
			return Key::Tab;
		case VK_CLEAR:
			//unused Key
			break;
		case VK_RETURN:
			return Key::Enter;
		case VK_SHIFT:
			return Key::LeftShift;
		case VK_CONTROL:
			return Key::LeftControl;
		case VK_MENU:
			return Key::LeftAlt;
		case VK_PAUSE:
			return Key::Pause;
		case VK_CAPITAL:
			return Key::CapsLock;
		case VK_ESCAPE:
			return Key::Escape;
		case VK_SPACE:
			return Key::Space;
		case VK_PRIOR:
			return Key::Period;
		case VK_NEXT:
			return Key::PageDown;
		case VK_END:
			return Key::End;
		case VK_HOME:
			return Key::Home;
		case VK_LEFT:
			return Key::Left;
		case VK_UP:
			return Key::Up;
		case VK_RIGHT:
			return Key::Right;
		case VK_DOWN:
			return Key::Down;
		case VK_PRINT:
			return Key::PrintScreen;
		case VK_INSERT:
			return Key::Insert;
		case VK_DELETE:
			return Key::Delete;

	/*
	 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	 * 0x3A - 0x40 : unassigned
	 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	 */

		case VK_LWIN:
			return Key::LeftSuper;
		case VK_RWIN:
			return Key::RightSuper;
		case VK_NUMPAD0:
			return Key::KP0;
		case VK_NUMPAD1:
			return Key::KP1;
		case VK_NUMPAD2:
			return Key::KP2;
		case VK_NUMPAD3:
			return Key::KP3;
		case VK_NUMPAD4:
			return Key::KP4;
		case VK_NUMPAD5:
			return Key::KP5;
		case VK_NUMPAD6:
			return Key::KP6;
		case VK_NUMPAD7:
			return Key::KP7;
		case VK_NUMPAD8:
			return Key::KP8;
		case VK_NUMPAD9:
			return Key::KP9;
		case VK_MULTIPLY:
			return Key::KPMultiply;
		case VK_ADD:
			return Key::KPAdd;
		case VK_SEPARATOR:
			return Key::KPDivide;
		case VK_SUBTRACT:
			return Key::KPSubtract;
		case VK_DECIMAL:
			return Key::KPDecimal;
		case VK_DIVIDE:
			return Key::KPDivide;
		case VK_F1:
			return Key::F1;
		case VK_F2:
			return Key::F2;
		case VK_F3:
			return Key::F3;
		case VK_F4:
			return Key::F4;
		case VK_F5:
			return Key::F5;
		case VK_F6:
			return Key::F6;
		case VK_F7:
			return Key::F7;
		case VK_F8:
			return Key::F8;
		case VK_F9:
			return Key::F9;
		case VK_F10:
			return Key::F10;
		case VK_F11:
			return Key::F11;
		case VK_F12:
			return Key::F12;
		case VK_F13:
			return Key::F13;
		case VK_F14:
			return Key::F14;
		case VK_F15:
			return Key::F15;
		case VK_F16:
			return Key::F16;
		case VK_F17:
			return Key::F17;
		case VK_F18:
			return Key::F18;
		case VK_F19:
			return Key::F19;
		case VK_F20:
			return Key::F20;
		case VK_F21:
			return Key::F21;
		case VK_F22:
			return Key::F22;
		case VK_F23:
			return Key::F23;
		case VK_F24:
			return Key::F24;

		case VK_NUMLOCK:
			return Key::NumLock;
		case VK_SCROLL:
			return Key::ScrollLock;

		case VK_OEM_NEC_EQUAL:   // '=' key on numpad
			return Key::KPEqual;
		  /*
		   * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
		   * Used only as parameters to GetAsyncKeyState() and GetKeyState().
		   * No other API or message will distinguish left and right keys in this way.
		   */
		case VK_LSHIFT:
			return Key::LeftShift;
		case VK_RSHIFT:
			return Key::RightShift;
		case VK_LCONTROL:
			return Key::LeftControl;
		case VK_RCONTROL:
			return Key::RightControl;
		case VK_LMENU:
			return Key::LeftAlt;
		case VK_RMENU:
			return Key::RightAlt;
		case VK_OEM_1:	// ';:' for US
			return Key::Semicolon;
		case VK_OEM_PLUS:		// '+' any country
			return Key::Equal;
		case VK_OEM_COMMA:		// ',' any country
			return Key::Comma;
		case VK_OEM_MINUS:		// '-' any country
			return Key::Minus;
		case VK_OEM_PERIOD:		// '.' any country
			return Key::Period;
		case VK_OEM_2:			// '/?' for US
			return Key::Slash;
		case VK_OEM_3:			// '`~' for US
			return Key::GraveAccent;
		}

		return (uint16_t)wp;
	}

	void Win32Window::CreateOpenGLContext()
	{
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		if (!(m_DC = GetDC(m_Window)))				// Did We Get A Device Context?
		{
			LastErrormsg();
			return;
		}
		int PixelFormat;
		if (!(PixelFormat = ChoosePixelFormat(m_DC, &pfd)))			// Did Windows Find A Matching Pixel Format?
		{
			LastErrormsg();
			return;
		}
		if (!SetPixelFormat(m_DC, PixelFormat, &pfd))				// Are We Able To Set The Pixel Format?
		{
			LastErrormsg();
			return;
		}
		if (!(m_RC = wglCreateContext(m_DC)))						// Are We Able To Get A Rendering Context?
		{
			LastErrormsg();
			return;
		}
		if (!wglMakeCurrent(m_DC, m_RC))							// Try To Activate The Rendering Context
		{
			LastErrormsg();
			return;
		}
	}

	bool Win32Window::WGLExtensionSupported(const char* extensionname)
	{
		// this is pointer to function which returns pointer to string with list of all wgl extensions
		PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;

		// determine pointer to wglGetExtensionsStringEXT function
		_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");

		if (strstr(_wglGetExtensionsStringEXT(), extensionname) == NULL)
		{
			// string was not found
			return false;
		}

		// extension is supported
		return true;
	}

}