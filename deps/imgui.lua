project "ImGui"
	kind "StaticLib"
	language "C++"
	architecture "x86_64"

	targetdir "../bin/%{cfg.buildcfg}"
	objdir "../obj/%{cfg.buildcfg}"
	
	includedirs { "imgui/", "imgui/examples/", "imgui/backends/", "imgui/misc/","glad/include", "glfw/include/" }

	files
	{
		"imgui/*.cpp",
		"imgui/backends/imgui_impl_glfw.cpp",
		"imgui/backends/imgui_impl_opengl3.cpp",

		"imgui/misc/cpp/imgui_stdlib.h",
		"imgui/misc/cpp/imgui_stdlib.cpp",
	}

	defines 
	{
		"IMGUI_IMPL_OPENGL_LOADER_GLAD"
	}
    
	filter "system:linux"
		pic "On"

		systemversion "latest"

		defines
		{
			"_IMGUI_X11"
		}

	filter "system:windows"
		systemversion "latest"

		defines 
		{ 
			"_IMGUI_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		optimize "on"