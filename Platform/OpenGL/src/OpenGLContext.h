#pragma once
#include "Base/Base.h"

#include "Renderer/GraphicsContext.h"

namespace Crank
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext();
		virtual ~OpenGLContext() override;

		virtual void Init(Window* window) override;
		void SwapBuffers() override;

		Window* m_Window;
	};
}