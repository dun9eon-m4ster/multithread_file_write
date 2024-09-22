#!/bin/bash

thread_count=$(cat /proc/cpuinfo | grep processor | wc -l)

rm ./build -rf
mkdir build
cd build
cmake ..
cmake --build . -j $thread_count
 