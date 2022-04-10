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

  os.mkdir("build")
  os.copyfile("tests/test.cgrf", "build")
  os.copyfile("tests/test_with_commented_lines.cgrf", "build")

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
