IncludeDir = {}
IncludeDir["spdlog"] = "%{wks.location}/vendor/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"

workspace "Crank"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "vendor/GLFW"
	--include "vendor/spdlog"
	--include "vendor/Glad"
	--include "vendor/imgui"
	--include "vendor/yaml-cpp"
group ""

group "Platforms"
	include "GLFWWindow"
	include "Win32Window"
group ""

include "Crank"
include "Sandbox"
