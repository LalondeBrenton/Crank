#pragma once

#include "Base/Base.h"
#include <string>

#include "Events/Event.h"
#include "Renderer/RendererAPI.h"

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
	};
}

extern "C"
{
	CGE_API bool CreateWindowAPI(Crank::Ref<Crank::Window>* object);
	typedef bool(*CREATEWINDOWAPI)(Crank::Ref<Crank::Window>* object);

	CGE_API bool ReleaseWindowAPI(Crank::Ref<Crank::Window>* object);
	typedef bool(*RELEASEWINDOWAPI)(Crank::Ref<Crank::Window>* object);
}