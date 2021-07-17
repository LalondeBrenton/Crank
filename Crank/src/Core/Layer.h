#pragma once

#include "Base/Base.h"
#include "Events/Event.h"


namespace Crank
{
	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer")
			: m_DebugName(debugName)
		{
		}

		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
