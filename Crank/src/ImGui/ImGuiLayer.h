#pragma once

#include "Core/Layer.h"

namespace Crank
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(void* window) :Layer("ImGuiLayer") {}
		~ImGuiLayer() = default;

		virtual void Begin() = 0;
		virtual void End() = 0;

		virtual void  BlockEvents(bool block) = 0;
	};
}