project "Win32Window"
	kind "SharedLib"
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

	defines
	{
		"CGE_PLATFORM_WINDOWS",
		"_CRT_SECURE_NO_WARNINGS",
		"BUILD_DLL"
	}

	includedirs
	{
		"%{wks.location}/Crank/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
	}

	links
	{
		"Crank",
		"ImGui",
		"opengl32.lib"
	}

	configuration "windows"
	postbuildcommands 
	{ 
		("{COPY} %{cfg.buildtarget.relpath} " .. bindir .. outputdir .. "/Sandbox")
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
