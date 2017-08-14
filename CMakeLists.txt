cmake_minimum_required(VERSION 3.9)

# We do not want build artifacts to be put in the source tree
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In Source builds are not allowed.")
endif()

# Uncomment to use verbose build outpu
#set(CMAKE_VERBOSE_MAKEFILE ON)

project(aegis
        VERSION 0.1.0
        DESCRIPTION "Aegis Game Programming Library")

add_subdirectory(src/aft)
add_subdirectory(src/aunit)
