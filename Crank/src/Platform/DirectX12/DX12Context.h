#pragma once
#include "Crank/Base/Base.h"

#include "Crank/Renderer/GraphicsContext.h"
#include "Crank/Window/Window.h"

namespace Crank
{
	class DX12Context : public GraphicsContext
	{
	public:
		DX12Context();
		virtual ~DX12Context() override;

		virtual void Init() override;
		virtual void SwapBuffers() override;

	};
}