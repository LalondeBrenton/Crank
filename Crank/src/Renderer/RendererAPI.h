#pragma once

#include "Base/Base.h"

#include "GraphicsContext.h"

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

		virtual RendererAPIs GetAPI() = 0;

		virtual void Init() = 0;

		virtual GraphicsContext* GetContext() = 0;
	};
}

extern "C"
{
	CGE_API bool CreateRendererAPI(Crank::RendererAPI** object);
	typedef bool(*CREATERENDERERAPI)(Crank::RendererAPI** object);

	CGE_API bool ReleaseRendererAPI(Crank::RendererAPI** object);
	typedef bool(*RELEASERENDERERAPI)(Crank::RendererAPI** object);
}