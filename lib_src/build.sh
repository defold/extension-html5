#!/usr/bin/env bash

# Run from this folder
# Builds a C++ library and moves it to the extension library folder

EMCC=$EMSCRIPTEN/em++
EMAR=$EMSCRIPTEN/emar

$EMCC -O3 testlib.cpp -c -o testlib.o

$EMAR rcs libtestlib.a testlib.o

mkdir -p ../html5nativeext/lib/js-web
mkdir -p ../html5nativeext/include

cp -v libtestlib.a ../html5nativeext/lib/web
cp -v testlib.h ../html5nativeext/include/libtestlib.h

rm testlib.o libtestlib.a
