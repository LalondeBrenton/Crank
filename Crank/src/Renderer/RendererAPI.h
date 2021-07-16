#pragma once

#include "Base/Base.h"

#include "ImGui/ImGuiLayer.h"

#include "GraphicsContext.h"

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

		virtual Ref<ImGuilayer> CreateImGuiLayer() = 0;
	};
}

extern "C"
{
	CGE_API bool CreateRendererAPI(Crank::Ref<Crank::RendererAPI>* object);
	typedef bool(*CREATERENDERERAPI)(Crank::Ref < Crank::RendererAPI>* object);

	CGE_API bool ReleaseRendererAPI(Crank::Ref < Crank::RendererAPI>* object);
	typedef bool(*RELEASERENDERERAPI)(Crank::Ref < Crank::RendererAPI>* object);
}