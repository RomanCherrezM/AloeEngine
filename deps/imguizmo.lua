project "IMGUIZMO"
	kind "StaticLib"
	language "C"
	architecture "x86_64"

	targetdir "../bin/%{cfg.buildcfg}"
	objdir "../obj/%{cfg.buildcfg}"
	
	includedirs 
	{
		"spdlog/",
		"imgui/"
		
	}

	files
	{
		"imguizmo/**.h",
		"imguizmo/**.cpp"
	}
    
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"