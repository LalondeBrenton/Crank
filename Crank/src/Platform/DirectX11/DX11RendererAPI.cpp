#include "pch.h"
#include "DX11rendererAPI.h"
#include "DX11Context.h"
#include "DX11ImGuiLayer.h"


namespace Crank
{

	DX11RendererAPI::DX11RendererAPI()
		: m_GraphicsContext()
	{
		Init();
	}

	DX11RendererAPI::~DX11RendererAPI()
	{
	}

	void DX11RendererAPI::Init()
	{
		m_GraphicsContext = CreateRef<DX11Context>();
	}

	Ref<GraphicsContext> DX11RendererAPI::GetContext()
	{
		return m_GraphicsContext;
	}

	void DX11RendererAPI::SetClearColor(const glm::vec4& color)
	{
		static_cast<DX11Context*>(m_GraphicsContext.get())->SetClearColor(color);
	}

	void DX11RendererAPI::Clear()
	{
		static_cast<DX11Context*>(m_GraphicsContext.get())->Clear();
	}

	ImGuiLayer* DX11RendererAPI::CreateImGuiLayer()
	{
		return new DX11ImGuiLayer();
	}

}