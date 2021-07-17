#pragma once
#include "Crank/Base/Base.h"

#include "Crank/Renderer/GraphicsContext.h"

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