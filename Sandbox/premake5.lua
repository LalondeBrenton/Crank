project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir (bindir .. outputdir .. "/%{prj.name}")
	objdir (binintdir .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Crank/src",
		"%{IncludeDir.spdlog}"
	}

	links
	{
		"Crank"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"WIN32",
			"CGE_PLATFORM_WINDOWS"
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
