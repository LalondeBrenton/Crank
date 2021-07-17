#pragma once

#include "ImGui/ImGuiLayer.h"
#include "Window/Window.h"

namespace Crank
{
	class OpenGLImGuiLayer : public ImGuiLayer
	{
	public:
		OpenGLImGuiLayer(void* window);
		~OpenGLImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		virtual void Begin() override;
		virtual void End()override;

		virtual void BlockEvents(bool block) override { m_BlockEvents = block; }

	private:
		Window* m_Window;
		bool m_BlockEvents = true;

		void SetDarkThemeColors();
	};
}