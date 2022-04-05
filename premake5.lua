workspace "cgrf"
  configurations { "Debug", "Release" }
  platforms { "x64" }
  location "build"

project "cgrf"
  kind "ConsoleApp"
  language "C"
  cdialect "C99"
  warnings "Extra"
  targetname "cgrf"
  targetdir "build"

  os.copyfile("tests/test.cgrf", "build")
  buildoptions { "-pedantic" }
  includedirs { "src", "dep" }

  if os.host() == "windows" then
    links { "SDL2main", "SDL2", "opengl32" }
  elseif os.host() == "linux" then
    links { "SDL2main", "SDL2", "GL", "m" }
  end

  files { "src/**.c", "dep/**.c" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
