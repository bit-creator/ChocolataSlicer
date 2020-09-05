#!/bin/bash

# Detect architecture
CURRENT_ARCHITECTURE=""
. scipts/detectArchitecture.sh
echo "Architecture : ${CURRENT_ARCHITECTURE}"

# Platform deteching
CURRENT_PLATFORM=""
. scipts/detectPlatform.sh
echo "Platform : ${CURRENT_PLATFORM}"



BUILD_TYPE="Release"
GL_TARGET="ogl"
for i in "$@"
do
case $i in
    --buildtype=*)
        if [[ ${i#*=} == "Release" || ${i#*=} == "Debug" ]]; then
            BUILD_TYPE="${i#*=}"
        else
            echo "Build type is unknown. Use default type - Release"
        fi
    ;;
    --gltarget=*)
        CINDER_GL_TARGET="${i#*=}"
    ;;
    --arch=*)
        CURRENT_ARCHITECTURE="${i#*=}"
    ;;
    --platform=*)
        CURRENT_PLATFORM="${i#*=}"
    ;;
esac
done



# Required tools deteching
. scipts/detectTools.sh

# Install packages
. scipts/installPackages.sh

# Install and build Cinder
. scipts/installCinder.sh
