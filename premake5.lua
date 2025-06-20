workspace "Pongus Maximus"
    configurations {"Debug", "Release"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
        kind "ConsoleApp"

    filter "configurations:Release"
        optimize "On"
        kind "WindowedApp"

    project "raylib"
        kind "StaticLib"
        language "C"
        cdialect "C99"
        staticruntime "On"
        location "libs"

        -- Include directories
        includedirs { "vendor/raylib/src", "vendor/raylib/src/external/glfw/include" }

        -- Source files
        files {
            "vendor/raylib/src/*.h",
            "vendor/raylib/src/*.c"
        }

        -- Preprocessor defines
        filter "configurations:Debug"
            runtime "Debug"
            symbols "On"
            defines { "DEBUG", "SUPPRESS_DEF_PLATFORM" }

        filter "configurations:Release"
            runtime "Release"
            optimize "On"
            defines { "NDEBUG", "SUPPRESS_DEF_PLATFORM" }

        -- Platform-specific defines and settings
        filter { "system:windows" }
            defines { "PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33" }
            systemversion "latest"
            links { "opengl32", "winmm", "gdi32", "shell32" }

        filter { "system:linux" }
            defines { "PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33", "_GLFW_X11" }
            links { "GL", "X11", "pthread", "m", "dl" }

        filter { "system:macosx" }
            defines { "PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33" }
            links { "Cocoa.framework", "OpenGL.framework", "CoreAudio.framework",
                    "AudioToolbox.framework", "CoreVideo.framework", "IOKit.framework" }
    
    project "Pongus_Maximus"
        location "build/"
        language "C++"
        cppdialect "C++20"

        files {"src/**.cpp", "src/**.hpp"}
        includedirs {"src/", "vendor/raylib/src", "vendor/json/include"}

	filter "system:windows"
	    links {"raylib", "winmm", "gdi32"}

	filter "system:linux"
	    links {"raylib"}

    
