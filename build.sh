#!/bin/sh

if [ "$1" = "r" ]; then
  echo ==================RELEASE================== && mkdir -p build
  premake5 gmake2 && make -C build config=release
else
  echo ===================DEBUG=================== && mkdir -p build
  premake5 gmake2 && make -C build config=debug
fi
