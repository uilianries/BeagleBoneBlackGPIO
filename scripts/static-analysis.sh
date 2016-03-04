#!/bin/bash

static_analyser=cppcheck
target_dir=src/

check_analyser() {
    if hash ${static_analyser} 2>/dev/null; then
        echo "Static analysis using ${static_analyser}"
    else
        "Could not find ${static_analyser}. Please, check if is installed."
        exit 1
    fi
}

execute_checker() {
    ${static_analyser} ${target_dir} --enable=all --inconclusive --std=c++11 --suppress=missingIncludeSystem --language=c++ --check-config
    if [ $? -ne 0 ]; then
        echo "Static analysis was failed!"
        exit $?
    fi
}

main() {
    check_analyser
    execute_checker
    exit 0
}

main
