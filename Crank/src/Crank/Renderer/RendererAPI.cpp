#include "pch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLrendererAPI.h"

namespace Crank
{

	Ref<RendererAPI> RendererAPI::Create(RendererAPIs api)
	{
		return CreateRef<OpenGLRendererAPI>();
	}

}