#!/bin/bash

clang_version=3.6
linter=clang-tidy-${clang_version}
target='src/*pp test/*pp'

check_program() {
    if hash ${linter} 2>/dev/null; then
        echo "Check programmer errors (Linter)"
    else
        echo "Could not find ${linter}. Please, check if is installed"
        exit 1
    fi
}

execute_linter() {
    ${linter} ${target} -- -Isrc -std=c++11
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
