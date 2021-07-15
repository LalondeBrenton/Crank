#pragma once

namespace Crank
{
	class Window;

	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init(Window* window) = 0;
		virtual void SwapBuffers() = 0;
	};
}