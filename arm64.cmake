# Cross-compilation system information.
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# The sysroot contains all the libraries we might need to link against and
# possibly headers we need for compilation.
#set(CMAKE_SYSROOT /var/lib/schroot/chroots/ubuntu-focal-arm64)
#set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
set(CMAKE_LIBRARY_ARCHITECTURE aarch64-linux-gnu)

# Install path when SYSROOT is read-only.
# set(CMAKE_STAGING_PREFIX aarch64-staging)

# Set the compilers for C, C++ and Fortran.
set(GCC_TRIPLE "aarch64-linux-gnu")
set(CMAKE_C_COMPILER ${GCC_TRIPLE}-gcc CACHE FILEPATH "C compiler")
set(CMAKE_CXX_COMPILER ${GCC_TRIPLE}-g++ CACHE FILEPATH "C++ compiler")
set(CMAKE_Fortran_COMPILER ${GCC_TRIPLE}-gfortran CACHE FILEPATH "Fortran compiler")

# Automatically use the cross-wrapper for pkg-config when available.
set(PKG_CONFIG_EXECUTABLE aarch64-linux-gnu-pkg-config CACHE FILEPATH "pkg-config executable")

# Set the architecture-specific compiler flags.
#set(ARCH_FLAGS "-mcpu=cortex-a53+crc+simd")
set(ARCH_FLAGS "")
set(CMAKE_C_FLAGS_INIT ${ARCH_FLAGS})
set(CMAKE_CXX_FLAGS_INIT ${ARCH_FLAGS})
set(CMAKE_Fortran_FLAGS_INIT ${ARCH_FLAGS})

# Don't look for programs in the sysroot (these are ARM programs, they won't run
# on the build machine).
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Only look for libraries, headers and packages in the sysroot, don't look on
# the build machine.
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE arm64)

