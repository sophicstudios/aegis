cmake_minimum_required(VERSION 3.11)

# We do not want build artifacts in the source tree
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In Source builds are not allowed.")
endif()

# Uncomment to use verbose build output
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CXX_STANDARD_REQUIRED ON)

project(aegis
        VERSION 0.1.0
        DESCRIPTION "Aegis Game Programming Library")

add_subdirectory(src/aft)
add_subdirectory(src/agt)
add_subdirectory(src/aunit)
