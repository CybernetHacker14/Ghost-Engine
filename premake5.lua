include "./vendor/premake/premake_customization/solution_items.lua"

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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Ghost/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Ghost/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Ghost/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Ghost/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Ghost/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Ghost/vendor/entt/include"

group "Dependencies"
	include "vendor/premake"
	include "Ghost/vendor/GLFW"
	include "Ghost/vendor/Glad"
	include "Ghost/vendor/imgui"
group ""

include "Ghost"
include "Sandbox"
include "Ghost-Editor"