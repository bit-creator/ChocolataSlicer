#!/bin/bash


if [[ -e "build/Release/ChocolataSlicer/ChocolataSlicer" ]]; then 
    ./${pwd}/build/Release/ChocolataSlicer/ChocolataSlicer

elif [[ -e "build/Debug/ChocolataSlicer/ChocolataSlicer" ]]; then
    ./${pwd}/build/Debug/ChocolataSlicer/ChocolataSlicer

else 
    echo "Try to compile ChocolataSlicer again...
    ERR : Executable file didn't find.
    "

fi 
