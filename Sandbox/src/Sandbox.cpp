#include <iostream>

#include "Crank.h"

class ExampleLayer : public Crank::Layer
{
public:
	void OnAttach() override
	{
		CGE_WARN("Attached Example Layer");
	}
	void OnEvent(Crank::Event& event) override
	{
		//if ((event.GetEventType() == Crank::EventType::KeyTyped) ||
		//	(event.GetEventType() == Crank::EventType::WindowResize))
			CGE_TRACE(event.ToString());
	}

};

class Sandbox : public Crank::Application
{
public:
	Sandbox(Crank::ApplicationCommandLineArgs args)
	{
		PushLayer(new ExampleLayer());
	}
};

Crank::Application* Crank::CreateApplication(Crank::ApplicationCommandLineArgs args)
{
	return new Sandbox(args);
}