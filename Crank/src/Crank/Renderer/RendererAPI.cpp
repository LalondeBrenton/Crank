#include "pch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLrendererAPI.h"
#include "Platform/DirectX11/DX11RendererAPI.h"

namespace Crank
{

	Ref<RendererAPI> RendererAPI::Create(RendererAPIs api)
	{
		switch (api)
		{
		case Crank::RendererAPIs::OpenGL:
			return CreateRef<OpenGLRendererAPI>();
		case Crank::RendererAPIs::DirectX11:
			return CreateRef<DX11RendererAPI>();
		case Crank::RendererAPIs::DirectX12:
			CGE_CORE_ASSERT(0, "DirectX 12 unsupported!");
		default:
			CGE_CORE_ASSERT(0, "Unknown RendererAPI!");
		}
		
	}

}