workspace "Saragan2D"
	configurations { "Debug", "Release" }
	
	architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"ThirdParty/glew/include/**.h"
	}

	includedirs
	{
		"SaraganEngine"
		"ThirdParty/glm/include"
	}

	links
	{
		"SaraganEngine"
	}

	libdirs  
	{
		"ThirdParty/glew/lib/Release/x64/**"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"
		links { "SaraganEngine", "OpenGL32" }

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
		"ThirdParty/glew/include"
	}

	libdirs  
	{
		"ThirdParty/glew/lib/Release/x64/**"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"
		links { "OpenGL32" }

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
