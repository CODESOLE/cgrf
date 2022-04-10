# CGRF
[![build-windows](https://github.com/CODESOLE/cgrf/actions/workflows/build-windows.yml/badge.svg)](https://github.com/CODESOLE/cgrf/actions/workflows/build-windows.yml) 
[![build-linux](https://github.com/CODESOLE/cgrf/actions/workflows/build-linux.yml/badge.svg)](https://github.com/CODESOLE/cgrf/actions/workflows/build-linux.yml) 
[![build-macos](https://github.com/CODESOLE/cgrf/actions/workflows/build-macos.yml/badge.svg)](https://github.com/CODESOLE/cgrf/actions/workflows/build-macos.yml)

A very simple c graph visualization.

# Build on Windows
 - Install [MSYS2](https://msys2.org) (Leave installation directory to `C:\msys64`)
 - Open `MSYS2 MSYS` shell from start menu (**NOT `MSYS2 MINGW or others`**)
 - Change directory to the root of this folder and then run `./install_deps_for_windowsmsys2_and_arch_linux.sh` from `MSYS2 MSYS` shell ( it will install necessary dependencies)
 - Then close `MSYS2 MSYS` shell and open `MSYS2 MINGW64` shell, change directory to the root of this folder, run `./build.sh` this will create a `build` directory and write build files and compiled binary there (You can run `./build.sh r` to compile with release mode otherwise it will compile default to debug mode)

# Build on Linux
For Archlinux and its derivatives (which uses pacman package manager) you can run `./install_deps_for_windowsmsys2_and_arch_linux.sh` (if needed run with sudo), then run `./build.sh` (You can run `./build.sh r` to compile with release mode otherwise it will compile default to debug mode)

For other linux distributions you can install dependencies according to your package manager:
 - GCC
 - GNU Make
 - Premake
 - SDL2

Then just run `./build.sh` from root directory (No need for `./install_deps_for_windowsmsys2_and_arch_linux.sh` other than arch linux like distributions)
