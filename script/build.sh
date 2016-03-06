#!/bin/bash

builder=cmake

check_program() {
    if hash ${builder} 2>/dev/null; then
        echo "Build with ${builder}"
    else
        echo "Could not find ${builder}. Please, check if is installed"
        exit 1
    fi
}

execute_build() {
    mkdir build
    cd build
    cmake ..
    if [ $? -ne 0 ]; then
        exit 1
    fi
    make
    if [ $? -ne 0 ]; then
        exit 1
    fi
}

main() {
    check_program
    execute_build
}

main
