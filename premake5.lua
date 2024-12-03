workspace "AloeEngine"

    location("build/")

    configurations { "Debug", "Release" }
    startproject "AloeGame"

    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines { "RELEASE", "NDEBUG" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }
        runtime "Release"

project "AloeCore"
	kind "StaticLib"
	language "C++"
    cppdialect "C++17"
	architecture "x86_64"
    
    filter "action:vs*"
        buildoptions { "/utf-8" }

    includedirs { 
        "AloeCore/", 
        "deps/stb/", 
        "deps/glad/include/", 
        "deps/glfw/include/", 
        "deps/glm/", "deps/imgui/", 
        "deps/imgui/examples", 
        "deps/yaml/include/", 
        "deps/entt/",  
        "deps/box2d/include/",
        "deps/spdlog/",
        "deps/imguizmo/"
    }
    
    files { "AloeCore/**.cpp", "AloeCore/**.h" }

    links { "GLFW", "GLM", "GLAD", "ImGui", "YAML", "BOX2D", "IMGUIZMO"}

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }


project "AloeEditor"

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

	includedirs
	{
		"AloeCore/",
        "AloeEditor/",

        "deps/stb/", 
        "deps/glad/include/", 
        "deps/glfw/include/", 
        "deps/glm/", "deps/imgui/", 
        "deps/yaml/include/",  
        "deps/entt/" , 
        "deps/box2d/include/",
        "deps/imguizmo/"
	}

	files 
	{		
		"AloeCore/**.h",
        "AloeEditor/Editor/**.h",
		"AloeEditor/Editor/**.cpp",

        "AloeEditor/main.cpp",
	}

    filter "system:linux"
    links { "dl", "pthread" }
        defines { "_X11"}

    filter "system:windows"
        defines { "_WINDOWS" }
	
	links { "AloeCore" }


project "AloeProject"

    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

	includedirs
	{
		"AloeCore/",
		"AloeProject/",

        "deps/stb/", 
        "deps/glad/include/", 
        "deps/glfw/include/", 
        "deps/glm/", "deps/imgui/", 
        "deps/yaml/include/",  
        "deps/entt/",
	}

    files
    {
        "AloeProject/**.h",
        "AloeProject/**.cpp",
    }

    prebuildcommands
    {
         "python \"" .. path.getabsolute(path.join(os.getcwd(), "tools/Build", "code_gen.py")) .. "\""
    }

    filter "system:linux"
    links { "dl", "pthread" }
        defines { "_X11"}

    filter "system:windows"
        defines { "_WINDOWS" }

    links { "AloeCore" }


group "Dependencies"
    include "deps/glfw.lua"
    include "deps/glad.lua"
    include "deps/glm.lua"
    include "deps/imgui.lua"
    include "deps/yaml.lua"
    include "deps/entt.lua"
    include "deps/box2d.lua"
    include "deps/imguizmo.lua"
