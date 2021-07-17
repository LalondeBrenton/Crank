#include "pch.h"
#include "OpenGLrendererAPI.h"
#include "OpenGLContext.h"
#include "OpenGLImGuiLayer.h"

#include <glad/glad.h>

namespace Crank
{
	bool OpenGLRendererAPI::s_Initialized = false;

	OpenGLRendererAPI::OpenGLRendererAPI()
		: m_GraphicsContext(nullptr)
	{
		if (!Log::IsInitalized())
			Log::Init();
	}

	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
		if (m_GraphicsContext)
			m_GraphicsContext = nullptr;
	}

	void OpenGLRendererAPI::Init()
	{
		m_GraphicsContext = CreateRef< OpenGLContext>();

		s_Initialized = true;
	}

	Ref<GraphicsContext> OpenGLRendererAPI::GetContext()
	{
		if (!s_Initialized) Init();
		return m_GraphicsContext;
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