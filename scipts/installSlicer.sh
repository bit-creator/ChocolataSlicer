#!/bin/bash

installSlicer() {
    echo "Configuring ChocolataSlicer:"
    command mkdir build &> /dev/null
    cd build
    cmake ../ -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCINDER_TARGET_GL=$GL_TARGET
    make -j4

    echo "ChocolataSlicer configured"

}

installSlicer
