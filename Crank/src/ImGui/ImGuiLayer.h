#pragma once

#include "Core/Layer.h"

namespace Crank
{
	class ImGuilayer : public Layer
	{

	public:
		virtual void Begin() = 0;
		virtual void End() = 0;

		void SetDarkThemeColors();

	};
}