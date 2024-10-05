require "vendor/premake-ecc/ecc"

workspace "OpenGL-Template"
  configurations { 'Debug', 'Release' }
  startproject "OpenGL-Template"

  flags { "MultiProcessorCompile" }

  filter "configurations:Debug"
    defines { "DEBUG", "DEBUG_SHADER" }
    symbols "On"

  filter "configurations:Release"
    defines { "RELEASE" }
    optimize "Speed"
    flags { "LinkTimeOptimization" }

project "OpenGL-Template"
  kind "WindowedApp"
  language "C"

  targetdir "bin/%{cfg.buildcfg}"
  objdir "obj/%{cfg.buildcfg}"

  includedirs { "vendor/glad/include", "vendor/glfw/include", "vendor/cglm/include", "vendor/stb_image" }

  files
  {
    "src/**.h",
    "src/**.c",
  }

  links { "GLFW", "CGLM", "GLAD", "STB_IMAGE" }

  filter "system:linux"
    links { "dl", "pthread", "m" }
    defines { "_X11" }

  filter "system:windows"
    defines { "_WINDOWS" }

include "vendor/glfw.lua"
include "vendor/glad.lua"
include "vendor/cglm.lua"
include "vendor/stb_image.lua"
