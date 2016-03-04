#!/bin/bash

linter=clang-tidy-3.5
target_dir=src

check_program() {
    if hash ${linter} 2>/dev/null; then
        echo "Check programmer errors (Linter)"
    else
        echo "Could not find ${linter}. Please, check if is installed"
        exit 1
    fi
}

execute_linter() {
    ${linter} ${target_dir}/*pp -- -std=c++11
    if [ $? -ne 0 ]; then
        echo "Linter was failed!"
        exit $?
    fi
}

main() {
    check_program
    execute_linter
    exit 0
}

main
