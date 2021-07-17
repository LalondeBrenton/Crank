#pragma once
#include <string>

#include "Crank/Base/Base.h"

#include "Crank/Events/Event.h"
#include "Crank/Renderer/RendererAPI.h"

namespace Crank
{
	enum class WindowAPIs
	{
		WindowAPIGLFW,
		WindowAPIWIN32
	};

	struct WindowProperties
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(const std::string& title = "Crank Graphics Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual WindowAPIs GetAPI() = 0;

		virtual void Init(const WindowProperties& props, Ref<RendererAPI> rendererapi) = 0;

		virtual void OnUpdate() = 0;
		virtual void SwapBuffers() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual void* GetProcAddress() const = 0;

		virtual bool ImGuiInit() = 0;
		virtual void ImGuiNewFrame() = 0;
		virtual void ImGuiShutdown() = 0;
		virtual void MakeCurrentRenderContext() = 0;

		static Ref<Window> Create(WindowAPIs api);
	};
}