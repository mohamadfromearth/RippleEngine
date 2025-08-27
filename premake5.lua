workspace "RippleEngine"
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
IncludeDir["GLFW"] = "RippleEngine/vendor/GLFW/include"

include "RippleEngine/vendor/GLFW"


project "RippleEngine"
	location "RippleEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "rppc.h"
	pchsource "RippleEngine/src/rppc.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

links 
	{ 
		"GLFW",
		"opengl32.lib",
		 "legacy_stdio_definitions.lib"  
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RP_PLATFORM_WINDOWS",
			"RP_BUILD_DLL"
		}

		

	filter "configurations:Debug"
		defines "RP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RP_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RP_DIST"
		optimize "On"
		
	
	filter "action:vs*"
      buildoptions { "/utf-8" }

	  
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"RippleEngine/vendor/spdlog/include",
		"RippleEngine/src"
	}

	links
	{
		"RippleEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22621.0"

		defines
		{
			"RP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RP_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RP_DIST"
		optimize "On"
	
		
	filter "action:vs*"
      buildoptions { "/utf-8" }	