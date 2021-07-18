#include "pch.h"
#include "OpenGLRendererAPI.h"
#include "OpenGLContext.h"
#include "OpenGLImGuiLayer.h"

#include <glad/glad.h>

namespace Crank
{

	OpenGLRendererAPI::OpenGLRendererAPI()
	{
		Init();
	}

	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
	}

	void OpenGLRendererAPI::Init()
	{
		m_GraphoicsContext = CreateRef<OpenGLContext>();
	}

	Ref<GraphicsContext> OpenGLRendererAPI::GetContext()
	{
		return m_GraphoicsContext;
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		::glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	ImGuiLayer* OpenGLRendererAPI::CreateImGuiLayer()
	{
		return new OpenGLImGuiLayer();
	}

}