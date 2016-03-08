#!/bin/bash

if [ $1 == '-h' ] || [ $1 == '--help' ]; then
    echo "Verify BeagleBoneBlackGPIO project dependencies"
    exit 0
fi

apt_packages=(doxygen valgrind cppcheck g++ cmake git clang-3.6 clang-format-3.6)
libs_dir=(/usr/include /usr/local/include)

check_program() {
    for program in ${apt_packages[*]}; 
    do
        if hash ${program} 2>/dev/null; then
            echo "INFO: Package ${program} is present"
        else
            echo "WARNING: Package ${program} is not present"
            sudo apt-get install -y -qq ${program}
            if [ $? -ne 0 ]; then
                echo "ERROR: Could not install package ${program}. Please, verify."
                exit 1
            fi
        fi
    done
}

check_boost() {

    lib_found=0
    for dir in ${libs_dir[*]};
    do
        if [ -d ${dir}/boost ]
        then
            echo "INFO: libboost was found"
            lib_found=1
            break
        fi
    done

    if [ $lib_found -eq 0 ];
    then
        echo "WARNING: libboost not found"
        sudo apt-get install -y -qq libboost-all-dev
        if [ $? -ne 0 ]; then
            echo "ERROR: Could not install libboost"
            exit 1
        fi
    fi
}

check_poco() {

    lib_found=0
    for dir in ${libs_dir[*]};
    do
        if [ -d ${dir}/Poco ]
        then
            echo "INFO: libpoco was found"
            lib_found=1
            break
        fi
    done

    if [ $lib_found -eq 0 ];
    then
        echo "WARNING: libpoco not found."
        wget http://pocoproject.org/releases/poco-1.7.0/poco-1.7.0.tar.gz
        if [ $? -ne 0 ]; then
            echo "ERROR: Could not download Poco library"
            exit 1
        fi
        tar zxf poco-1.7.0.tar.gz
        if [ $? -ne 0 ]; then
            echo "ERROR: Could not extract files from Poco library"
            exit 1
        fi
        cd poco-1.7.0
        ./configure --static --shared --no-samples --no-tests
        if [ $? -ne 0 ]; then
            echo "ERROR: Could not configure Poco library"
            exit 1
        fi
        echo "INFO: Get a coffee, Poco library build will start now"
        sleep 5
        make -j4 && make install
        if [ $? -ne 0 ]; then
            echo "ERROR: Could not build Poco library"
            exit 1
        fi

    fi
}

main() {
    check_program
    check_boost
    check_poco
    echo "INFO: All dependencies are solved"
}

main
