#pragma once

#include "Base/Base.h"
#include "Application.h"

//#ifdef CGE_PLATFORM_WINDOWS

extern Crank::Application* Crank::CreateApplication(Crank::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Crank::Log::Init();
	CGE_CORE_INFO("Creating Application");
	auto app = Crank::CreateApplication({ argc, argv });
	CGE_CORE_INFO("Running Application");
	app->Run();
	delete app;
}

//#endif
