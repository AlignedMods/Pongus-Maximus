workspace "Pongus Maximus"
    configurations {"Debug", "Release"}

    filter "configurations:Debug"
            defines {"DEBUG"}
            symbols "On"
            kind "ConsoleApp"

    filter "configurations:Release"
        optimize "On"
        kind "WindowedApp"

    project "Pongus_Maximus"
        location "build/"
        language "C++"

        files {"src/**.cpp", "src/**.hpp"}
        includedirs {"src/"}

        libdirs {}