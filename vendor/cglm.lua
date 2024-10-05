project "CGLM"
  kind "StaticLib"
  language "C"

  targetdir "../bin/%{cfg.buildcfg}"
  objdir "../obj/%{cfg.buildcfg}"

  includedirs { "cglm/include/" }
  files { "stc/**.c" }

  filter "system:linux"
    pic "On"

    systemversion "latest"
    staticruntime "On"

    defines { "_CGLM_X11" }

  filter "system:windows"
    systemversion "latest"
    staticruntime "On"

    defines 
    {
      "_CGLM_WIN32",
      "_CRT_SECURE_NO_WARNINGS"
    }

  filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    runtime "Release"
    optimize "on"
