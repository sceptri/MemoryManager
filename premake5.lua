workspace "MemoryManagment"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release"
	}
	
	files
	{
		"premake5.lua"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MemoryMamager"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/".. outputdir .."/")
	objdir("bin-int/".. outputdir .."/")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
    	{
        	"src/headers"
    	}

    	filter "system:linux"
        	buildoptions {"-std=c++17"}
    
    	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"
