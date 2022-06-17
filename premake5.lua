workspace "Gem"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["glm"] = "Gem/vendor/glm"

group "Dependencies"
	include "Gem/vendor/GLFW"
	include "Gem/vendor/Glad"
	include "Gem/vendor/imgui"
group ""

project "Gem"
	location "Gem"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	pchheader "gempch.h"
	pchsource "Gem/src/gempch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
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
		systemversion "latest"

		defines
		{
			"GEM_PLATFORM_WINDOWS",
			"GEM_EXPORT_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines 
		{
			"GEM_DEBUG",
			"GEM_ENABLE_ASSERTS",
			"GEM_ENABLE_VERIFY"
		}
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GEM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GEM_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Gem/src",
		"Gem/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Gem"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"GEM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GEM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GEM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GEM_DIST"
		runtime "Release"
		optimize "On" 