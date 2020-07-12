workspace "Ghost"
	architecture "x64"
	startproject "Sandbox"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Ghost/vendor/GLFW/include"
IncludeDir["Glad"] = "Ghost/vendor/Glad/include"
IncludeDir["ImGui"] = "Ghost/vendor/imgui"

group "Dependencies"
include "Ghost/vendor/GLFW"
include "Ghost/vendor/Glad"
include "Ghost/vendor/imgui"

group ""

project "Ghost"
	location "Ghost"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "gtpch.h"
	pchsource "Ghost/src/gtpch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	
	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"GT_PLATFORM_WINDOWS",
			"GT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "GT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GT_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"Ghost/vendor/spdlog/include",
		"Ghost/src"
	}

	links{
		"Ghost"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"GT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GT_DIST"
		runtime "Release"
		optimize "On"