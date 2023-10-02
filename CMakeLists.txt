cmake_minimum_required (VERSION 3.13)
project (matekbd-keyboard-display VERSION 23.9.1 LANGUAGES C)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "..." FORCE)
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Options

option (ENABLE_WERROR "Treat all build warnings as errors" OFF)

set(CMAKE_BUILD_TYPE "Release")

if (ENABLE_WERROR)
    add_definitions ("-Werror")
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions ("-Weverything")
else ()
    add_definitions ("-Wall")
endif ()

# Prerequisites

include (GNUInstallDirs)
find_package (PkgConfig REQUIRED)
include (FindPkgConfig)
pkg_check_modules (DEPS REQUIRED libxklavier gtk+-3.0 libmatekbdui atk)

# Build

add_subdirectory (src)
add_subdirectory (data)
add_subdirectory (man)

# Info

message (STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message (STATUS "Build with -Werror: ${ENABLE_WERROR}")
