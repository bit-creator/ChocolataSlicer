#!/bin/bash

CURRENT_PATH=$(pwd)
CINDER_PATH=${CURRENT_PATH}/ChocolataSliser/Cinder
function exitWithError() {
    echo "Error:" "$@" >&2
    exit 1
}


function buildDeps() {
    for tool in git make cmake; do
        command -v "${tool}" &> /dev/null || exitWithError ". . . Missing required tool ${tool}"
    done

    # Clone LibCinder to folder
    if [[ ! -s "${CINDER_PATH}" ]]; then
        echo ". . . Cinder is not cloned yet, cloning now"
        git clone --recursive https://github.com/cinder/Cinder.git \
            || exitWithError "Cannot clone Cinder"

        mv "${CURRENT_PATH}/Cinder" "${CINDER_PATH}"
    fi

    # Build LibCinder
    if [ ! -f "${CINDER_PATH}/build/CMakeCache.txt" ] ; then
        echo ". . . Cinder has not been configure, running cmake ..."
        cd ${CINDER_PATH}
        mkdir build
        cd build
        cmake .. || exitWithError ". . . Cannot run CMake on Cinder"
        make -j4 || exitWithError ". . . Error building Cinder"
        cd ../../../
    fi

}

function prepareEnv() {
    sudo apt-get install libxcursor-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    zlib1g-dev \
    libfontconfig1-dev \
    libmpg123-dev \
    libsndfile1 \
    libsndfile1-dev \
    libpulse-dev \
    libasound2-dev \
    libcurl4-gnutls-dev \
    libgstreamer1.0-dev \
    libgstreamer-plugins-bad1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    gstreamer1.0-libav \
    gstreamer1.0-alsa \
    gstreamer1.0-pulseaudio \
    gstreamer1.0-plugins-bad \
    libboost-filesystem-dev \
    zenity
}

function buildSlicer() {
    if [[ ! -e "${CURRENT_PATH}/CMakeCache.txt" ]]; then
        echo ". . . ChocolataSlicer has not been configure, running cmake ..."
        mkdir build
        cd build
        cmake .. || exitWithError ". . . Cannot run CMake on ChocolataSclicer"
        make -j 4 || exitWithError ". . . Error building ChocolataSlicer"
    fi

}

# Entry point
prepareEnv
buildDeps
buildSlicer
echo ". . . Dependencies successfully built"
