outputDir = "%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}"

workspace "CoreTrace"
	architecture "x64"
	configurations {"DEBUG", "DIST", "RELEASE"}

include "premake-core.lua"
