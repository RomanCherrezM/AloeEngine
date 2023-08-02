workspace "AloeProject"

    location("build")

    configurations { "Debug", "Release" }
    startproject "AloeGame"

    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }

project "AloeEngine"
	kind "StaticLib"
	language "C++"
    cppdialect "C++17"
	architecture "x86_64"
    
    includedirs { "AloeEngine/src/", "deps/glad/include/", "deps/glfw/include/", "deps/glm/", "deps/imgui/", "deps/imgui/examples" }
    
    files { "AloeEngine/src/**.cpp", "AloeEngine/src/**.h" }

    links { "GLFW", "GLM", "GLAD", "ImGui" }

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }

project "AloeGame"

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

	includedirs
	{
		"AloeEngine/src/",
		"AloeGame/src/",
        "deps/glm"
	}

	files 
	{		
		"AloeEngine/src/**.h",
		"AloeGame/src/**.h",
		"AloeGame/src/**.cpp",

        "AloeGame/main.cpp",
	}

    filter "system:linux"
    links { "dl", "pthread" }
        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }
	
	links { "AloeEngine" }

project "AloeEditor"

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

	includedirs
	{
		"AloeEngine/src/",
		"AloeGame/src/",
        "AloeEditor/src/",
	}

	files 
	{		
		"AloeEngine/src/**.h",
		"AloeGame/src/**.h",
		"AloeGame/src/**.cpp",
        "AloeEditor/src/**.h",
		"AloeEditor/src/**.cpp",

        "AloeEditor/main.cpp",
	}

    filter "system:linux"
    links { "dl", "pthread" }
        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }
	
	links { "AloeEngine" }

    
group "Dependencies"
    include "deps/glfw.lua"
    include "deps/glad.lua"
    include "deps/glm.lua"
    include "deps/imgui.lua"
