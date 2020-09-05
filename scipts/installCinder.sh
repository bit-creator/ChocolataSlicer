#!/bin/bash

installCinder() {
    echo "Configuring libcinder:"
    if [[ ! -d "${HOME}/Cinder" ]]; then
        echo "Clonning Cinder..."
        command git clone --recursive "https://github.com/cinder/Cinder.git" ${HOME}/Cinder
    fi

    CINDER_BUILD_FOLDER=""
    if [[ $BUILD_TYPE == "Debug" ]]; then
        CINDER_BUILD_FOLDER="${HOME}/Cinder/buildDebug"
    else
        CINDER_BUILD_FOLDER="${HOME}/Cinder/buildRelease"
    fi

    if [[ $CURRENT_ARCHITECTURE == "x86_64" ]]; then
        GL_TARGET="ogl"
    else
        GL_TARGET="es2-rpi"
    fi


    if [[ ! -d $CINDER_BUILD_FOLDER ]]; then 
        mkdir $CINDER_BUILD_FOLDER
        cd $CINDER_BUILD_FOLDER
        cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCINDER_TARGET_GL=$GL_TARGET

        make -j4
    fi

    echo "Cinder configured"

}

installCinder
