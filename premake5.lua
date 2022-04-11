workspace "cgrf"
  configurations { "Debug", "Release" }
  location "build"

project "cgrf"
  kind "ConsoleApp"
  language "C"
  cdialect "C99"
  warnings "Extra"
  targetname "cgrf"
  targetdir "build"
  prebuildcommands { "{RMDIR} tests", "{COPYDIR} ../tests tests" }
  buildoptions { "-pedantic" }
  includedirs { "src", "dep" }
  links { "SDL2main", "SDL2", "m" }
  files { "src/**.c", "dep/**.c" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"
  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
