#include "pch.h"
#include "DX12rendererAPI.h"
#include "DX12Context.h"
#include "DX12ImGuiLayer.h"


namespace Crank
{
	bool DX12RendererAPI::s_Initialized = false;

	DX12RendererAPI::DX12RendererAPI()
		: m_GraphicsContext(nullptr)
	{
	}

	DX12RendererAPI::~DX12RendererAPI()
	{
	}

	void DX12RendererAPI::Init()
	{
	}

	Ref<GraphicsContext> DX12RendererAPI::GetContext()
	{
		return CreateRef<DX12Context>();
	}

	void DX12RendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void DX12RendererAPI::Clear()
	{
	}

	ImGuiLayer* DX12RendererAPI::CreateImGuiLayer()
	{
		return new DX12ImGuiLayer();
	}

}