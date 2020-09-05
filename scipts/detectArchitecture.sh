#!/bin/bash

detecArchitecture() {
    CURRENT_FULL_ARCHITECTURE=$(dpkg --print-architecture)

    if [[ $CURRENT_FULL_ARCHITECTURE =~ "arm" ]]; then
        CURRENT_ARCHITECTURE="arm"
    else
        CURRENT_ARCHITECTURE="x86_64"
    fi
}

detecArchitecture
