workspace "ucode"
    configurations { "Debug", "Release" }
    gccprefix ""

	filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Full"
		buildoptions { "-flto"}
		linkoptions { "-flto"}

-------------------------------
project "ucode"
    kind "ConsoleApp"
    language "C++"
    targetdir   "bin/%{cfg.buildcfg}"
    objdir      "bin/%{cfg.buildcfg}/obj"
  
    defines {
        --"_CRT_SECURE_NO_WARNINGS",
    }
  
    includedirs {
		"src",
		"json-c",
		"json-c/build",
		"regex",
    }

	files {
        "main.c",
    }

    filter "system:Windows"
		links {
			"user32",
            "kernel32",
            "shlwapi"
	     }

	links { "ws2_32", "engine", "math" }

---------------------------------

project "math"
    kind "SharedLib"
    language "C++"
    targetdir   "bin/%{cfg.buildcfg}"
    objdir      "bin/%{cfg.buildcfg}/modules/obj"

	includedirs {
		"src",
		"json-c",
		"json-c/build",
		"regex",
    }

	files {
        "libs/math.c",
    }		 

	links { "engine" }

---------------------------------

project "engine"
	kind "SharedLib"
    language "C++"
    targetdir   "bin/%{cfg.buildcfg}"
    objdir      "bin/%{cfg.buildcfg}/engine/obj"

	includedirs {
		"src",
		"json-c",
		"json-c/build",
		"regex",
    }

	files {
        "src/*.c",
		"regex/c-regex.c",
		"json-c/*.c",
    }

	links { "ws2_32" }	