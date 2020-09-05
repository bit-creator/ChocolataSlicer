#!/bin/bash

detectPlatform() {
    if [[ $(uname -a | grep Ubuntu) ]]; then
        CURRENT_PLATFORM="Ubuntu"
    elif [[ $(uname -a | grep Fedora) ]]; then
        CURRENT_PLATFORM="Fedora"
    else
        CURRENT_PLATFORM="..."
    fi

}

detectPlatform
