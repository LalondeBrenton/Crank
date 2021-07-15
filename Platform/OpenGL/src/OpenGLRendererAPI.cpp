#include "OpenGLrendererAPI.h"
#include "OpenGLContext.h"

namespace Crank
{
	bool OpenGLRendererAPI::s_Initialized = false;

	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
		if (m_GraphicsContext)
			delete m_GraphicsContext;
	}

	void OpenGLRendererAPI::Init()
	{
		m_GraphicsContext = new OpenGLContext();

		s_Initialized = true;
	}

	GraphicsContext* OpenGLRendererAPI::GetContext()
	{
		if (!s_Initialized) Init();
		return m_GraphicsContext;
	}

}

CGE_API bool CreateRendererAPI(Crank::RendererAPI** object)
{
	if (!*object)
	{
		*object = new Crank::OpenGLRendererAPI();
		return true;
	}
	return false;
}

CGE_API bool ReleaseRendererAPI(Crank::RendererAPI** object)
{
	if (!*object)
	{
		return false;
	}
	delete* object;
	*object = nullptr;
	return true;
}