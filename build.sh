#!/bin/bash

CURRENT_ARCHITECTURE=""
CURRENT_PLATFORM=""

BUILD_TYPE="Release"
GL_TARGET="ogl"



. scipts/detectArchitecture.sh
echo "Architecture : ${CURRENT_ARCHITECTURE}"


. scipts/detectPlatform.sh
echo "Platform : ${CURRENT_PLATFORM}"
echo ""



if [[ $CURRENT_ARCHITECTURE == "arm" ]]; then
    GL_TARGET="es2-rpi"
fi



for i in "$@"
do
case $i in
    -buildtype=*)
        if [[ ${i#*=} == "Release" || ${i#*=} == "Debug" ]]; then
            BUILD_TYPE="${i#*=}"
        else
            echo "Err : Build type is unknown. Use default type - Release"
        fi
    ;;
    --arch=*)
        if [[ ${i#*=} == "arm" || ${i#*=} == "x86_64" ]]; then
            CURRENT_ARCHITECTURE="${i#*=}"
        else
            echo "Err : Seted architecture is unknown. Use default arch - x86_64"
            CURRENT_ARCHITECTURE="x86_64"
        fi
    ;;

    -gltarget=*)
        GL_TARGET="${i#*=}"
    ;;
    --platform=*)
        CURRENT_PLATFORM="${i#*=}"
    ;;
esac
done




. scipts/detectTools.sh
. scipts/installPackages.sh

. scipts/installCinder.sh

. scipts/installSlicer.sh
echo "
ChocolataSlicer ready to work!"
