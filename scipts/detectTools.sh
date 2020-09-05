#!/bin/bash

detectTools() {
    _errs=0

    echo "Tools deteching:"
    for tool in g++ git make cmake; do
        if [[ $(command -v "${tool}" &> /dev/null) ]]; then
            echo "   Required tool does not exist : ${tool}. Install it before continue"
            echo " - ${tool} : MISSED"
            
            _errs=$((_errs+1))
        else
            echo " - ${tool} : EXIST"
        fi
    done

    if (( $_errs > 0)); then
        echo ""
        echo "Required tools are missed"
        echo "Err : You should manually install missed tools to continue work!"
        exit $_errs
    fi
}

echo ""
detectTools