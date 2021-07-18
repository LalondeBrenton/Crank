#pragma once
#include "Crank/Base/Base.h"

#include "Crank/Renderer/RendererAPI.h"

namespace Crank
{
	class DX12RendererAPI : public RendererAPI
	{
	public:
		DX12RendererAPI();
		virtual ~DX12RendererAPI() override;

		virtual RendererAPIs GetAPI() override { return RendererAPIs::DirectX12; }

		virtual void Init() override;

		virtual Ref<GraphicsContext> GetContext() override;


		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		virtual ImGuiLayer* CreateImGuiLayer() override;

	private:
		static bool s_Initialized;
		Ref<GraphicsContext> m_GraphicsContext;
	};
}