#pragma once
#include "Base/Base.h"

#include "Renderer/RendererAPI.h"

namespace Crank
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI() : m_GraphicsContext(nullptr) {}
		virtual ~OpenGLRendererAPI() override;

		virtual RendererAPIs GetAPI() override { return RendererAPIs::OpenGL; }

		virtual void Init() override;

		virtual GraphicsContext* GetContext() override;

	private:
		static bool s_Initialized;
		GraphicsContext* m_GraphicsContext;
	};
}