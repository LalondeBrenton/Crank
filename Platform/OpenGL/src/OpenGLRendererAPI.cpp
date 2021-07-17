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

	Ref<ImGuiLayer> OpenGLRendererAPI::CreateImGuiLayer(void* window)
	{
		return CreateRef<OpenGLImGuiLayer>(window);
	}

}

CGE_API bool CreateRendererAPI(Crank::Ref<Crank::RendererAPI>* object)
{
	if (!*object)
	{
		*object = Crank::CreateRef<Crank::OpenGLRendererAPI>();
		return true;
	}
	return false;
}

CGE_API bool ReleaseRendererAPI(Crank::Ref<Crank::RendererAPI>* object)
{
	if (!*object)
	{
		return false;
	}
	*object = nullptr;
	return true;
}