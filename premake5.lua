workspace "Pong-OpenGL"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["imgui"] = "vendor/imgui"

include "vendor/GLFW"
include "vendor/Glad"
include "vendor/imgui"

project "Pong-OpenGL"
	location "Pong-OpenGL"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/utf-8"

		defines
		{
			"FL_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "FL_DEBUG"
			buildoptions "/MTd"
			symbols "On"

		filter "configurations:Release"
			defines "FL_RELEASE"
			buildoptions "/MT"
			optimize "On"

		filter "configurations:Dist"
			defines "FL_DIST"
			buildoptions "/MT"
			optimize "On"
