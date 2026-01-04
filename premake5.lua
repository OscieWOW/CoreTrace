outputDir = "%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}"

workspace "CoreTrace"
	architecture "x64"
	configurations {"DEBUG", "DIST", "RELEASE"}

project "CoreTrace"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir("bin/"..outputDir.."/%{prj.name}")
	objdir("bin-int/"..outputDir.."/%{prj.name}")

	files {
		"src/**.cpp",
		"src/**.h",
		"Examples/**.cpp",
		"Examples/**.h"
	}

	filter "system:linux"
		systemversion "latest"
		defines {
			"PLATFORM_LINUX"
		}
		
	filter "configurations:DEBUG"
		defines "DEBUG"
		symbols "on"

	filter "configurations:DIST"
		defines "DIST"
		symbols "on"
		optimize "on"

	filter "configurations:RELEASE"
		defines "RELEASE"
		optimize "on"
