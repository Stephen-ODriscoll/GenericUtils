#!/bin/bash

mkdir -p build
cd build
cmake .. -D CMAKE_CXX_STANDARD=20 -D CMAKE_BUILD_TYPE=Release
cd ..
