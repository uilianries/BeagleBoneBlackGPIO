#!/bin/bash

log_file=valgrind.log

if [[ $# -eq 0 ]]; then
    echo "Input is empty"
    echo "Usage: $0 <application-path>"
    exit 1
fi

if [ ! -e "$1" ]; then
    echo "$1 is an invalid path."
    exit 1
fi

if hash valgrind 2>/dev/null; then
    echo "Memory leak check (Valgrind)"
else
    echo "Could not find valgrind. Please, check if is installed"
    exit 1
fi

valgrind --tool=memcheck --leak-check=full $1 &> ${log_file}

cat ${log_file}

fgrep '*** No errors detected' ${log_file}
if [ $? -ne 0 ]; then
    echo "Unit Test failed"
    exit 1
else
    echo "Unit test finished with success"
fi

fgrep "ERROR SUMMARY: 0 errors" ${log_file}
if [ $? -ne 0 ]; then
    echo "Error: leak detected"
    exit 1
else
    echo "No leak detected"
fi

exit 0
