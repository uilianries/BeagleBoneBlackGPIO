#!/bin/bash

file_sufix=pp
format_style=Webkit
clang_version=3.6
formatter=clang-format-${clang_version}

check_clang_format() {
    if hash ${formatter} 2>/dev/null; then
        echo "INFO: Format all .*${file_sufix} to ${format_style} style"
    else
        echo "ERROR: Could not find ${formatter}. Please, check if is installed"
        exit 1
    fi
}

format_files() {
    for i in $(find -type f -name "*${file_sufix}"); do
        echo "INFO: Format file ${i}"
        ${formatter} -i -style=${format_style} $i
    done
}

main () {
    check_clang_format
    format_files
    exit 0
}

main
