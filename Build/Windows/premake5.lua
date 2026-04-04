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
    files{"../../src/Event/**.h"}
    files{"../../src/Event/**.cpp"}
    files{"../../src/Event/**.hpp"}
    files{"../../src/Layer/**.h"}
    files{"../../src/Layer/**.cpp"}
    files{"../../src/Layer/**.hpp"}
    files{"../../src/Window/**.h"}
    files{"../../src/Window/**.cpp"}
    files{"../../src/Window/**.hpp"}
    files{"../../src/Ecs/**.h"}
    files{"../../src/Ecs/**cpp"}
    files{"../../src/Ecs/**.hpp"}
    
    includedirs {"../../vendor/extern/include"}
    includedirs {"../../vendor/zap/include"}
    includedirs {"../../vendor/magic_enum"}
    includedirs {"../../vendor/entt"}

    cppdialect "C++17"

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
    files {"../../vendor/extern/glad.c"}
    includedirs {"../../src/"}
    includedirs {"../../src/"}
    includedirs {"../../src/"}

    includedirs {"../../vendor/extern/include"}
    includedirs {"../../vendor/zap/include"}
    includedirs {"../../vendor/magic_enum"}
    includedirs {"../../vendor/entt"}

    libdirs {"./Project/Sandbox/bin"}

    libdirs {"../../vendor/extern/lib"}

    links{"Mira", "Zap", "glfw3", "opengl32", "user32", "gdi32", "shell32", "freetype", "assimp"}
    cppdialect "C++17"

    filter "configurations:Debug"
        libdirs{"../../vendor/extern/lib/Debug"}
        libdirs{"../../vendor/zap/lib/Debug"}
        links{"zlibstaticd"}
        defines {"ZAP_CONSOLE_APPLICATION"}
        runtime "Debug"

    filter "configurations:Release"
        libdirs{"../../vendor/extern/lib/Release"}
        libdirs{"../../vendor/zap/lib/Release"}
        links{"zlibstatic"}
        defines {"ZAP_CONSOLE_APPLICATION"}
        runtime "Release"

    filter "configurations:Distribution"
        libdirs{"../../vendor/extern/lib/Release"}
        libdirs{"../../vendor/zap/lib/Release"}
        links{"zlibstatic"}    
        kind "WindowedApp"
        defines {"ZAP_WINDOW_ONLY_APPLICATION"}

    filter "action:vs*"
        flags { "multiprocessorcompile" }