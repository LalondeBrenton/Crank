#pragma once

#include "Crank/ImGui/ImGuiLayer.h"

namespace Crank
{
	class OpenGLImGuiLayer : public ImGuiLayer
	{
	public:
		OpenGLImGuiLayer();
		~OpenGLImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		virtual void Begin() override;
		virtual void End()override;

		virtual void BlockEvents(bool block) override { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;

		void SetDarkThemeColors();
	};
}