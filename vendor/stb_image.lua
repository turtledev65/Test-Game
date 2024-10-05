project "STB_IMAGE"
  kind "StaticLib"
  language "C"

  targetdir "../bin/%{cfg.buildcfg}"
  objdir "../obj/%{cfg.buildcfg}"

  includedirs { "stb_image/" }
  files { "stb_image/stb_image.c" }

  filter "system:linux"
    pic "On"

    systemversion "latest"
    staticruntime "On"

    defines { "_STB_IMAGE_X11" }

  filter "system:windows"
    systemversion "latest"
    staticruntime "On"

    defines 
    {
      "_STB_IMAGE_WIN32",
      "_CRT_SECURE_NO_WARNINGS"
    }

  filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    runtime "Release"
    optimize "on"
