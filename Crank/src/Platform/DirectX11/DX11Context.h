#pragma once
#include "Crank/Base/Base.h"

#include "Crank/Renderer/GraphicsContext.h"
#include "Crank/Window/Window.h"

#include <d3d11.h>

namespace Crank
{
	class DX11Context : public GraphicsContext
	{
	public:
		friend class DX11ImGuiLayer;
		friend class Win32Window;

		DX11Context();
		virtual ~DX11Context() override;

		virtual void Init() override;
		virtual void SwapBuffers() override;

		void SetClearColor(const glm::vec4& color);
		void Clear();

		void SetRenderTarget();

	private:
		ID3D11Device* m_Device;
		IDXGISwapChain* m_SwapChain;
		ID3D11DeviceContext* m_DeviceContext;
		ID3D11RenderTargetView* m_RenderTargetView;

		float m_Color[4];
	};
}