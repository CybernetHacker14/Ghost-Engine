project "Ghost-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{wks.location}/Ghost/vendor/spdlog/include",
		"%{wks.location}/Ghost/src",
		"%{wks.location}/Ghost/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"Ghost"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "GT_DEBUG"
		runtime "Debug"
		symbols "on"
		
		postbuildcommands
		{
			"{COPY} %{LibraryDir.VulkanSDK_DebugDLL} %{cfg.targetdir}"
		}

	filter "configurations:Release"
		defines "GT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GT_DIST"
		runtime "Release"
		optimize "on"
