#!/bin/bash

file_sufix=pp
format_style=Webkit
formatter=clang-format-3.5

check_clang_format() {
    if hash ${formatter} 2>/dev/null; then
        echo "Format all .*${file_sufix} to ${format_style} style"
    else
        echo "Could not find ${formatter}. Please, check if is installed"
        exit 1
    fi
}

format_files() {
    for i in $(find -type f -name "*${file_sufix}"); do
        ${formatter} -i -style=${format_style} $i
    done
}

main () {
    check_clang_format
    format_files
    exit 0
}

main
