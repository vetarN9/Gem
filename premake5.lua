workspace "Gem"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Gem/vendor/GLFW/include"
IncludeDir["Glad"] = "Gem/vendor/Glad/include"
IncludeDir["imgui"] = "Gem/vendor/imgui"

include "Gem/vendor/GLFW"
include "Gem/vendor/Glad"
include "Gem/vendor/imgui"

project "Gem"
	location "Gem"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	pchheader "gempch.h"
	pchsource "Gem/src/gempch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
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
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GEM_PLATFORM_WINDOWS",
			"GEM_EXPORT_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines 
		{
			"GEM_DEBUG",
			"GEM_ENABLE_ASSERTS",
			"GEM_ENABLE_VERIFY"
		}
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "GEM_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "GEM_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Gem/vendor/spdlog/include",
		"Gem/src"
	}

	links
	{
		"Gem"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GEM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GEM_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "GEM_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "GEM_DIST"
		buildoptions "/MD"
		optimize "On" 