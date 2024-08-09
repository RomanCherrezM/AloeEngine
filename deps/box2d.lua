project "BOX2D"
    kind "StaticLib"
    language "C++"
    architecture "x86_64"

    targetdir "../bin/%{cfg.buildcfg}"
    objdir "../obj/%{cfg.buildcfg}"
    
    includedirs { "box2d/include/" }

    files
    {
        "box2d/**.h",
        "box2d/**.cpp"
    }
    
    filter "system:linux"
        pic "On"
        systemversion "latest"

    filter "system:windows"
        systemversion "latest"
        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "on"