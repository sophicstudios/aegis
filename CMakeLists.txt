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
        VERSION 1.0.0
        DESCRIPTION "Aegis Game Programming Library")

find_package(PNG REQUIRED)
message(STATUS "PNG_INCLUDE_DIRS: " ${PNG_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_INCLUDE_DIR: " ${OPENGL_INCLUDE_DIR})

add_definitions(-DGL_SILENCE_DEPRECATION)

add_subdirectory(src/aunit)
add_subdirectory(src/aft)
add_subdirectory(src/agt)

set(AEGIS_HEADERS ${aft_HEADERS} ${agt_HEADERS})
message(STATUS "AEGIS_HEADERS: ${AEGIS_HEADERS}")

add_library(aegis SHARED $<TARGET_OBJECTS:agt> $<TARGET_OBJECTS:aft>)

target_link_libraries(aegis PUBLIC ${PNG_LIBRARIES} ${OPENGL_LIBRARIES})

install(TARGETS aegis 
    LIBRARY DESTINATION lib/aegis
)

install(FILES ${AEGIS_HEADERS} DESTINATION include/aegis)