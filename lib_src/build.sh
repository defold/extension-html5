# Run from this folder
# Builds a C++ library and moves it to the extension library folder

EMCC=/Users/mathiaswesterdahl/work/defold/tmp/dynamo_home/ext/bin/emsdk_portable/emscripten/1.35.0/em++
EMAR=/Users/mathiaswesterdahl/work/defold/tmp/dynamo_home/ext/bin/emsdk_portable/emscripten/1.35.0/emar

$EMCC -O3 testlib.cpp -c -o testlib.o

$EMAR rcs libtestlib.a testlib.o

mkdir -p ../html5nativeext/lib/js-web
mkdir -p ../html5nativeext/include

cp -v libtestlib.a ../html5nativeext/lib/js-web
cp -v testlib.h ../html5nativeext/include/libtestlib.h

#rm testlib.o libtestlib.a