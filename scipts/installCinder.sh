#!/bin/bash

installCinder() {
    echo "Configuring libcinder:"
    if [[ ! -d "${HOME}/Cinder" ]]; then
        echo "Clonning Cinder..."
        command git clone --recursive "https://github.com/cinder/Cinder.git" ${HOME}/Cinder
    fi


    CINDER_BUILD_FOLDER="${HOME}/Cinder/build_${GL_TARGET}/${BUILD_TYPE}"
    echo $CINDER_BUILD_FOLDER


    if [[ ! -d $CINDER_BUILD_FOLDER ]]; then 
        mkdir -p $CINDER_BUILD_FOLDER
        cd $CINDER_BUILD_FOLDER
        cmake ../../ -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCINDER_TARGET_GL=$GL_TARGET

        make -j4
    fi

    echo "Cinder configured"

}

installCinder
