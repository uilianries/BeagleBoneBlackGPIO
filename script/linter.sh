#!/bin/bash

linter=clang-tidy-3.6
log_file=test/linter.log
target=

if [[ $# -eq 0 ]]; then
    target='src/*pp test/*pp'
    echo "Input is empty, using default target: ${target}"
else
    target="$@"
fi

check_program() {
    if hash ${linter} 2>/dev/null; then
        echo "Check programmer errors (Linter)"
    else
        echo "Could not find ${linter}. Please, check if is installed"
        exit 1
    fi
}

execute_linter() {
    ${linter} -checks=-*,clang-analyzer-*,-clang-analyzer-alpha* ${target} -- -std=c++11 -Isrc 2>&1 | tee /dev/stderr | fgrep "warnings generated"
    if [ $? -eq 0 ]; then
        echo "Error: Linter found some warning"
        exit 1
    fi
}

main() {
    check_program
    execute_linter
}

main
