#!/bin/bash

log_file=doc/doxygen.log

check_program() {
    if hash doxygen 2>/dev/null; then
        echo "Generate documentation by Doxygen"
    else
        echo "Could not find doxygen. Please, check if is installed"
        exit 1
    fi
}

execute_doxygen() {
    doxygen doc/Doxyfile &> ${log_file} 
    fgrep 'warning:' ${log_file}
    if [ $? -eq 0 ]; then
        echo "Error $? : Doxygen reported some warning"
        exit 1
    fi
}

main () {
    check_program
    execute_doxygen
    exit 0
}

main
