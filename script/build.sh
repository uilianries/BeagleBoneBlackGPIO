#!/bin/bash

builder=cmake
install=0

if [ $# -eq 1 ]; then
    case $1 in
        -h|--help)
        echo "Build BeagleBoneBlackGPIO with CMake"
        echo "usage:"
        echo "    -h|--help     Display this message "
        echo "    -i|--install  Same as 'make && make install'"
        exit 0
        ;;
        -i|--install)
        eval install=1
        ;;
        *)
        echo "ERROR: Unknown argument"
        exit 1
        ;;
    esac
fi

check_program() {
    if hash ${builder} 2>/dev/null; then
        echo "Build with ${builder}"
    else
        echo "Could not find ${builder}. Please, check if is installed"
        exit 1
    fi
}

execute_build() {
    if [ ! -d build ]; then
        mkdir build
    fi
    cd build
    cmake ..
    if [ $? -ne 0 ]; then
        echo "ERROR: Could not build project with CMake"
        exit 1
    fi
    make
    if [ $? -ne 0 ]; then
        echo "ERROR: Cold not make project"
        exit 1
    fi
    if [ ${install} -eq 1 ]; then
        sudo make install
        if [ $? -ne 0 ]; then
            echo "ERROR: Could not install project"
            exit 1
        fi
    fi
}

main() {
    check_program
    execute_build
}

main
