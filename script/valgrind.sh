#!/bin/bash

log_file='script/valgrind.log'
target='build/test/test_gpio'

if [[ $# -eq 0 ]]; then
    echo "WARNING: Input is empty, default test is ${target}"
else
    eval target=$1
fi

if [ ! -e ${target} ]; then
    echo "ERROR: ${target} is an invalid path."
    exit 1
fi

if hash valgrind 2>/dev/null; then
    echo "INFO: Memory leak check (Valgrind)"
else
    echo "ERROR: Could not find valgrind. Please, check if is installed"
    exit 1
fi

valgrind --tool=memcheck --leak-check=full ${target} &> ${log_file}

cat ${log_file}

fgrep '*** No errors detected' ${log_file}
if [ $? -ne 0 ]; then
    echo "ERROR: Unit Test failed"
    exit 1
else
    echo "INFO: Unit test finished with success"
fi

fgrep "ERROR SUMMARY: 0 errors" ${log_file}
if [ $? -ne 0 ]; then
    echo "ERROR: leak detected"
    exit 1
else
    echo "INFO: No leak detected"
fi

exit 0
