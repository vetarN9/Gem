workspace "Gem"
	architecture "x86_64"
	startproject "Test"

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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Gem/vendor/GLFW/include"
IncludeDir["Glad"] = "Gem/vendor/Glad/include"
IncludeDir["imgui"] = "Gem/vendor/imgui"
IncludeDir["glm"] = "Gem/vendor/glm"
IncludeDir["stb"] = "Gem/vendor/stb"

group "Dependencies"
	include "Gem/vendor/GLFW"
	include "Gem/vendor/Glad"
	include "Gem/vendor/imgui"
group ""

project "Gem"
	location "Gem"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	pchheader "gempch.h"
	pchsource "Gem/src/gempch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GEM_PLATFORM_WINDOWS",
			"GEM_EXPORT_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines 
		{
			"GEM_DEBUG",
			"GEM_ENABLE_ASSERTS",
			"GEM_ENABLE_VERIFY"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GEM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GEM_DIST"
		runtime "Release"
		optimize "on"

project "Test"
	location "Test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

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
		systemversion "latest"

		defines
		{
			"GEM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GEM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GEM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GEM_DIST"
		runtime "Release"
		optimize "on" 