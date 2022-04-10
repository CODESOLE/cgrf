#!/bin/sh

if [ "$1" = "r" ]; then
  premake5 gmake2 && make -C build config=release
else
  premake5 gmake2 && make -C build config=debug
fi
