#pragma once
#include "Crank/Base/Base.h"

#include "Crank/Renderer/GraphicsContext.h"
#include "Crank/Window/Window.h"

namespace Crank
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext();
		virtual ~OpenGLContext() override;

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		static bool GladInit;
	};
}