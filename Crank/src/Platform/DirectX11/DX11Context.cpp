#include "pch.h"
#include "DX11Context.h"

#include "Crank/Window/Window.h"
#include "Crank/Core/Application.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Crank
{

	DX11Context::DX11Context()
		:m_Device(nullptr), m_SwapChain(nullptr), m_DeviceContext(nullptr), m_RenderTargetView(nullptr)
	{
		m_Color[0] = m_Color[1] = m_Color[2] = m_Color[3] = 0.0f;
	}

	DX11Context::~DX11Context()
	{
		if (m_RenderTargetView)
		{
			m_RenderTargetView->Release();
			m_RenderTargetView = NULL;
		}
		if (m_SwapChain)
		{
			m_SwapChain->Release();
			m_SwapChain = NULL;
		}
		if (m_DeviceContext)
		{
			m_DeviceContext->Release();
			m_DeviceContext = NULL;
		}
		if (m_Device)
		{
			m_Device->Release();
			m_Device = NULL;
		}
	}

	void DX11Context::Init()
	{
		HWND window;
		if (Application::Get().GetWindow()->GetAPI() == WindowAPIs::WindowAPIWIN32)
			window = *((HWND*)Application::Get().GetWindow()->GetNativeWindow());
		else if (Application::Get().GetWindow()->GetAPI() == WindowAPIs::WindowAPIGLFW)
			window = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow()->GetNativeWindow());

		// Setup swap chain
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = window;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
		if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_Device, &featureLevel, &m_DeviceContext) != S_OK)
			CGE_CORE_ERROR("Error Setting up DirectX11 Device and Swapchain!");

		// Create a Temporary Render Target
		ID3D11Texture2D* pBackBuffer;
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_RenderTargetView);
		pBackBuffer->Release();
	}

	void DX11Context::SwapBuffers()
	{
		m_SwapChain->Present(1, 0);
	}

	void DX11Context::SetClearColor(const glm::vec4& color)
	{
		m_Color[0] = color.r;
		m_Color[1] = color.g;
		m_Color[2] = color.b;
		m_Color[3] = color.a;
	}

	void DX11Context::Clear()
	{
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, m_Color);
	}

	void DX11Context::SetRenderTarget()
	{
		m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, NULL);
	}

}