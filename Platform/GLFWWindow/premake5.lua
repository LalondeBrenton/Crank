project "GLFWWindow"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"CGE_PLATFORM_WINDOWS",
		"_CRT_SECURE_NO_WARNINGS",
		"BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{wks.location}/Crank/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"Crank",
		"GLFW",
		"opengl32.lib"
	}
	
	configuration "windows"
	postbuildcommands 
	{ 
		("{COPY} %{cfg.buildtarget.relpath} ../../bin/" .. outputdir .. "/Sandbox")
	}

	filter "system:windows"
		systemversion "latest"

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
