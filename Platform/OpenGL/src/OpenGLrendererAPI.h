#pragma once
#include "Base/Base.h"

#include "Renderer/RendererAPI.h"

namespace Crank
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI();
		virtual ~OpenGLRendererAPI() override;

		virtual RendererAPIs GetAPI() override { return RendererAPIs::OpenGL; }

		virtual void Init() override;

		virtual Ref<GraphicsContext> GetContext() override;


		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		virtual Ref<ImGuiLayer> CreateImGuiLayer(void* window) override;

	private:
		static bool s_Initialized;
		Ref<GraphicsContext> m_GraphicsContext;
	};
}