#pragma once
#include "Crank/Base/Base.h"

#include "Crank/Renderer/RendererAPI.h"

namespace Crank
{
	class DX11RendererAPI : public RendererAPI
	{
	public:
		DX11RendererAPI();
		virtual ~DX11RendererAPI() override;

		virtual RendererAPIs GetAPI() override { return RendererAPIs::DirectX11; }

		virtual void Init() override;

		virtual Ref<GraphicsContext> GetContext() override;


		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		virtual ImGuiLayer* CreateImGuiLayer() override;

	private:
		Ref<GraphicsContext> m_GraphicsContext;
	};
}