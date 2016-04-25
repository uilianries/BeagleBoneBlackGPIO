# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

SET(TOOLCHAIN_PATH /opt/gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf)

# specify the cross compiler
SET(CMAKE_C_COMPILER   ${TOOLCHAIN_PATH}/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/arm-linux-gnueabihf-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH "${TOOLCHAIN_PATH} ${TOOLCHAIN_PATH}/include")

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
