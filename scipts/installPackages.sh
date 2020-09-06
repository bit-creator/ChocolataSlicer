#!/bin/bash

installPackages() {
    echo ""
    echo "Installing/updating binary packages:"

    if [ $CURRENT_PLATFORM == "Ubuntu" ]; then
        if [ $CURRENT_ARCHITECTURE == "x86_64" ]; then
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
            zenity &> "/dev/null"
        elif [ $CURRENT_ARCHITECTURE == "arm" ]; then
            sudo apt-get install libxcursor-dev \
            libgles2-mesa-dev \
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
            libboost-filesystem-dev &> "/dev/null"
        fi
        echo "Packages installed"
    else
        echo "Sorry, we cant detect current platform to install packages automatically."
        echo "Try to install it manually, or write to ChocolataSlicer support team"
        echo "  Err : current platform : ${CURRENT_PLATFORM}"
    fi

    echo ""
}

installPackages
