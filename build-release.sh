#!/bin/sh

set -xe

mkdir build_release && cd build_release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
