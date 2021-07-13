#pragma once

#include "Interfaces\Window.h"
#include "Core/KeyCodes.h"

namespace Crank
{

	class Win32Window :public Window
	{
	public:

		Win32Window();
		virtual ~Win32Window();

		virtual void Init(const WindowProperties& props);

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }

	private:

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		virtual void Shutdown();
		static LRESULT __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);
		void LastErrormsg();
		std::wstring ConvertStringtoW(const std::string& text);

		static KeyCode WinToKeyCode(WPARAM wp);

		HWND m_Window;

		WindowData m_Data;
		LONG_PTR m_WindowData;
	};
}