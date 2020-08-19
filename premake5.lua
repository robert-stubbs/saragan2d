workspace "Saragan2D"
	configurations { "Debug", "Release" }
	
	architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Game"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	
	pchheader "GamePCH.h"
	pchsource "%{prj.name}/GamePCH.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"ThirdParty/glm/include/**.hpp",
		"ThirdParty/glm/include/**.inl",
		"ThirdParty/glew/include/**.h",
		"ThirdParty/freetype-gl/include/**.h"
	}

	includedirs
	{
		"Engine",
		"ThirdParty/glm/include",
		"ThirdParty/glew/include",
		"ThirdParty/freetype2",
		"ThirdParty/freetype-gl",
		"ThirdParty/OpenAL/include"
	}

	links
	{
		"Engine"
	}

	libdirs  
	{
		"ThirdParty/glew/lib/**",
		"ThirdParty/freetype2/lib",
		"ThirdParty/freetype-gl/lib",
		"ThirdParty/OpenAL/**"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"
		links { "SaraganEngine", "OpenGL32", "glew32", "OpenAL32", "freetype", "freetype-gl" }

	filter "configurations.Debug"
		defines { "SARAGAN_DEBUG" }
		symbols "On"

	filter "configurations.Release"
		defines { "SARAGAN_RELEASE" }
		optimize "On"

project "Engine"
	location "%{prj.name}"
	kind "StaticLib"
	language "C++"

	pchheader "EnginePCH.h"
	pchsource "%{prj.name}/EnginePCH.cpp"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"ThirdParty/glm/include/**.hpp",
		"ThirdParty/glm/include/**.inl",
		"ThirdParty/glew/include/**.h"
	}

	includedirs
	{
		"ThirdParty/glm/include",
		"ThirdParty/glew/include",
		"ThirdParty/freetype2",
		"ThirdParty/freetype-gl",
		"ThirdParty/OpenAL/include"
	}

	libdirs  
	{
		"ThirdParty/glew/lib/**",
		"ThirdParty/OpenAL/**"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"

		postbuildcommands
		{
			("{COPY} ../bin/" .. outputdir .. "/%{prj.name} ../bin/" .. outputdir .. "/SaraganGame")
		}

	filter "configurations.Debug"
		defines { "SARAGAN_DEBUG" }
		symbols "On"

	filter "configurations.Release"
		defines { "SARAGAN_RELEASE" }
		optimize "On"

project "SaraganGame"
	location "%{prj.name}"
	kind "WindowedApp"
	language "C++"
	
	pchheader "GamePCH.h"
	pchsource "%{prj.name}/GamePCH.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"ThirdParty/glm/include/**.hpp",
		"ThirdParty/glm/include/**.inl",
		"ThirdParty/glew/include/**.h",
		"ThirdParty/freetype-gl/include/**.h"
	}

	includedirs
	{
		"SaraganEngine",
		"ThirdParty/glm/include",
		"ThirdParty/glew/include",
		"ThirdParty/freetype2",
		"ThirdParty/freetype-gl",
		"ThirdParty/OpenAL/include"
	}

	links
	{
		"SaraganEngine"
	}

	libdirs  
	{
		"ThirdParty/glew/lib/**",
		"ThirdParty/freetype2/lib",
		"ThirdParty/freetype-gl/lib",
		"ThirdParty/OpenAL/**"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"
		links { "SaraganEngine", "OpenGL32", "glew32", "OpenAL32", "freetype", "freetype-gl" }

	filter "configurations.Debug"
		defines { "SARAGAN_DEBUG" }
		symbols "On"

	filter "configurations.Release"
		defines { "SARAGAN_RELEASE" }
		optimize "On"

project "SaraganEngine"
	location "%{prj.name}"
	kind "StaticLib"
	language "C++"

	pchheader "EnginePCH.h"
	pchsource "%{prj.name}/EnginePCH.cpp"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"ThirdParty/glm/include/**.hpp",
		"ThirdParty/glm/include/**.inl",
		"ThirdParty/glew/include/**.h"
	}

	includedirs
	{
		"ThirdParty/glm/include",
		"ThirdParty/glew/include",
		"ThirdParty/freetype2",
		"ThirdParty/freetype-gl",
		"ThirdParty/OpenAL/include"
	}

	libdirs  
	{
		"ThirdParty/glew/lib/**",
		"ThirdParty/OpenAL/**"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"

		postbuildcommands
		{
			("{COPY} ../bin/" .. outputdir .. "/%{prj.name} ../bin/" .. outputdir .. "/SaraganGame")
		}

	filter "configurations.Debug"
		defines { "SARAGAN_DEBUG" }
		symbols "On"

	filter "configurations.Release"
		defines { "SARAGAN_RELEASE" }
		optimize "On"
	
			

project "freetype-gl"
	location "ThirdParty/%{prj.name}"
	kind "StaticLib"
	language "C++"
		
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")
	
	files {
		"ThirdParty/%{prj.name}/**.h",
		"ThirdParty/%{prj.name}/**.c",
		"ThirdParty/glm/include/**.inl",
		"ThirdParty/glew/include/**.h"
	}
	
	includedirs
	{
		"ThirdParty/glew/include",
		"ThirdParty/freetype2",
	}

	libdirs  
	{
		"ThirdParty/glew/lib/**",
		"ThirdParty/freetype2/lib"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"
		

		postbuildcommands
		{
			("{COPY} ../../bin/" .. outputdir .. "/%{prj.name} ../../bin/" .. outputdir .. "/SaraganGame")
		}


	filter "configurations.Debug"
		defines { "SARAGAN_DEBUG" }
		symbols "On"

	filter "configurations.Release"
		defines { "SARAGAN_RELEASE" }
		optimize "On"