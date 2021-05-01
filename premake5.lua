include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Ghost"
	architecture "x86_64"
	startproject "Ghost-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "Ghost/vendor/GLFW"
	include "Ghost/vendor/Glad"
	include "Ghost/vendor/imgui"
	include "Ghost/vendor/yaml-cpp"
group ""

include "Ghost"
include "Sandbox"
include "Ghost-Editor"
