IncludeDir = {}
IncludeDir["spdlog"] = "%{wks.location}/vendor/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["glad"] = "%{wks.location}/vendor/glad/include"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"
IncludeDir["ImGui"] = "%{wks.location}/vendor/ImGui"

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
bindir = "%{wks.location}/bin/"
binintdir = "%{wks.location}/bin-int/"

group "Dependencies"
	include "vendor/premake"
	include "vendor/spdlog"
	include "vendor/GLFW"
	include "vendor/Glad"
	include "vendor/imgui"
	--include "vendor/yaml-cpp"
group ""

include "Crank"
include "Sandbox"
