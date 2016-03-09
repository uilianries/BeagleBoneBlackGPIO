#!/bin/bash

log_file=script/doxygen.log

check_program() {
    if hash doxygen 2>/dev/null; then
        echo "INFO: Generate documentation by Doxygen"
    else
        echo "ERROR: Could not find doxygen. Please, check if is installed"
        exit 1
    fi
}

execute_doxygen() {
    doxygen doc/Doxyfile &> ${log_file} 
    cat ${log_file}
    fgrep 'warning:' ${log_file}
    if [ $? -eq 0 ]; then
        echo "ERROR: Doxygen reported some warning"
        exit 1
    fi
}

main () {
    check_program
    execute_doxygen
    exit 0
}

main
