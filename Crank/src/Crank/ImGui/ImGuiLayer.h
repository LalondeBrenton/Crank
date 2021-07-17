#pragma once

#include "Crank/Core/Layer.h"

namespace Crank
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer() :Layer("ImGuiLayer") {}
		~ImGuiLayer() = default;

		virtual void Begin() = 0;
		virtual void End() = 0;

		virtual void  BlockEvents(bool block) = 0;
	};
}