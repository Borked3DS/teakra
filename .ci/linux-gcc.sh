#!/bin/bash -ex

mkdir build && cd build
cmake .. -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER_LAUNCHER=ccache \
    -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
    -DCMAKE_CXX_COMPILER=gcc-14 \
    -DCMAKE_C_COMPILER=gcc-14 \
    -DCMAKE_CXX_FLAGS="-lstdc++" \
    -DCMAKE_C_FLAGS="-lstdc++" \
    -DCMAKE_LINKER_TYPE="MOLD" \
    -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=mold -lstdc++" \
    -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=mold -lstdc++" 

ninja
