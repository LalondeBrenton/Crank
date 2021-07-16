#pragma once

#include "ImGui/ImGuiLayer.h"

namespace Crank
{
	class OpenGLImGuiLayer : public ImGuilayer
	{
	public:
		OpenGLImGuiLayer();
		~OpenGLImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;

	};
}