#!/bin/bash

static_analyser=cppcheck
target='src/*pp test/*pp sample/*pp include/bbbgpio/*pp'

if [[ $# -eq 0 ]]; then
    echo "WARNING: Input is empty, using default target: ${target}"
else
    eval target="$@"
fi

check_analyser() {
    if hash ${static_analyser} 2>/dev/null; then
        echo "INFO: Static analysis using ${static_analyser}"
    else
        "ERROR: Could not find ${static_analyser}. Please, check if is installed."
        exit 1
    fi
}

execute_checker() {
    ${static_analyser} ${target} --enable=all --inconclusive --std=c++11 --language=c++ --error-exitcode=1
    if [ $? -ne 0 ]; then
        echo "ERROR: Static analysis was failed!"
        exit $?
    fi
}

main() {
    check_analyser
    execute_checker
    exit 0
}

main
