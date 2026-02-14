workspace "Mira-Workspace"
    architecture "x64"
    location "Project"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

project "Mira"
    location "Project/Mira"
    kind "StaticLib"
    language "C++"
    files{"../../src/**.h"}
    files{"../../src/**.cpp"}
    files{"../../src/**.hpp"}

    filter "configurations:Debug"
        staticruntime "off"
        runtime "Debug"

    filter "action:vs*"
        flags { "multiprocessorcompile" }

project "Application"
    location "Project/Sandbox"  
    kind "ConsoleApp"

    files {"../../sandbox/**.h"}
    files {"../../sandbox/**.cpp"}
    files {"../../sandbox/**.hpp"}
    includedirs {"../../src/"}
    includedirs {"../../src/"}
    includedirs {"../../src/"}

    libdirs {"./Project/Sandbox/bin"}

    links{"Mira"}

    filter "configurations:Distribution"
        kind "WindowedApp"

    filter "action:vs*"
        flags { "multiprocessorcompile" }