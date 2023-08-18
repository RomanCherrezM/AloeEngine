project "YAML"
	kind "StaticLib"
	language "C++"
	architecture "x86_64"

	targetdir "../bin/%{cfg.buildcfg}"
	objdir "../obj/%{cfg.buildcfg}"
    
    includedirs { "yaml/include/" }

	files { 
		"yaml/src/**.h", 
		"yaml/src/**.cpp", 
		"yaml/include/**.h" 
	}

	defines { "YAML_CPP_STATIC_DEFINE" }
    
	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		optimize "on"