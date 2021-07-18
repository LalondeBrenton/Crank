project "Crank"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir (bindir .. outputdir .. "/%{prj.name}")
	objdir (binintdir .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",

		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
	}

	
	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"WIN32",
			"CGE_PLATFORM_WINDOWS"
		}

		links
		{
			"d3d11.lib",
			"dxgi.lib",
			"d3dcompiler.lib",
			"opengl32.lib",
		}

	filter "configurations:Debug"
		defines "CGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CGE_DIST"
		runtime "Release"
		optimize "on"
