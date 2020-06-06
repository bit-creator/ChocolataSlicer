#!/bin/bash

CURRENT_PATH=$(pwd)
CINDER_PATH=${CURRENT_PATH}/ChocolataSliser/Cinder

# Cinder cleaning
if [[ -e "${CINDER_PATH}/build" ]]; then
    echo ". . . Delete ${CINDER_PATH}/build"
    rm -rf ${CINDER_PATH}/build
fi


# Slicer cleaning
if [[ -e "${CURRENT_PATH}/build" ]]; then
    echo ". . . Delete ${CURRENT_PATH}/build"
    rm -rf ${CURRENT_PATH}/build
fi

if [[ -e "${CURRENT_PATH}/CMakeFiles" ]]; then
    echo ". . . Delete ${CURRENT_PATH}/CMakeFiles"
    rm -rf ${CURRENT_PATH}/CMakeFiles
fi

if [[ -e "${CURRENT_PATH}/Debug" ]]; then
    echo ". . . Delete ${CURRENT_PATH}/Debug"
    rm -rf ${CURRENT_PATH}/Debug
fi

if [[ -e "${CURRENT_PATH}/CMakeCache.txt" ]]; then
    echo ". . . Delete ${CURRENT_PATH}/CMakeCache.txt"
    rm -rf ${CURRENT_PATH}/CMakeCache.txt
fi

if [[ -e "${CURRENT_PATH}/cmake_install.cmake" ]]; then
    echo ". . . Delete ${CURRENT_PATH}/cmake_install.cmake"
    rm -rf ${CURRENT_PATH}/cmake_install.cmake
fi

if [[ -e "${CURRENT_PATH}/Makefile" ]]; then
    echo ". . . Delete ${CURRENT_PATH}/Makefile"
    rm -rf ${CURRENT_PATH}/Makefile
fi
