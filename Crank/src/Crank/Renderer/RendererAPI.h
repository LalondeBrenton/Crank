#pragma once

#include "Crank/Base/Base.h"

#include "Crank/ImGui/ImGuiLayer.h"

#include "Crank/Renderer/GraphicsContext.h"

#include <glm/glm.hpp>

namespace Crank
{
	enum class RendererAPIs
	{
		OpenGL
	};

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() {}
		virtual void Init() = 0;

		virtual RendererAPIs GetAPI() = 0;

		virtual Ref<GraphicsContext> GetContext() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual ImGuiLayer* CreateImGuiLayer() = 0;

		static Ref<RendererAPI> Create(RendererAPIs api);
	};
}