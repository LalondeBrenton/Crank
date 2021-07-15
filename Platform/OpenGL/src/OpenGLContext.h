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

	private:
		void InitWin32();
		void InitGLFW();

		Window* m_Window;
	};
}