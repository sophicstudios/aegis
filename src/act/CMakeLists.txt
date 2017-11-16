project(act)

################################################################################
# actp group
################################################################################

set(ACTP_SOURCES
    actp/actp_condition.cpp
    actp/actp_condition.h
    actp/actp_mutex.cpp
    actp/actp_mutex.h
    actp/actp_scopedlock.h
    actp/actp_semaphore.cpp
    actp/actp_semaphore.h
    actp/actp_thread.cpp
    actp/actp_thread.h
    actp/actp_threadattributes.cpp
    actp/actp_threadattributes.h
    actp/actp_threadutil.cpp
    actp/actp_threadutil.h
)

set(ACTP_SOURCES_TEST
    actp/actp_condition.t.cpp
    actp/actp_mutex.t.cpp
    actp/actp_semaphore.t.cpp
    actp/actp_thread.t.cpp
)

source_group(actp FILES ${ACTP_SOURCES})

################################################################################
# acts group
################################################################################

set(ACTS_SOURCES
    acts/acts_platform.cpp
    acts/acts_platform.h
)

set(ACTS_SOURCES_TEST)

source_group(acts FILES ${ACTS_SOURCES})

################################################################################
# act library
################################################################################

set(ACT_SOURCES
    ${ACTP_SOURCES}
    ${ACTS_SOURCES}
)

set(${PROJECT_NAME}_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/actp
    ${PROJECT_SOURCE_DIR}/acts
    CACHE INTERNAL "${PROJECT_NAME}: Include dirs" FORCE)

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS} ${aft_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${ACT_SOURCES})
target_link_libraries(${PROJECT_NAME} aft)

target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

################################################################################
# act unit tests
################################################################################

set(ACT_SOURCES_TEST
    ${ACTP_SOURCES_TEST}
    ${ACTS_SOURCES_TEST}
    act.t.cpp
)

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS} ${aft_INCLUDE_DIRS} ${aunit_INCLUDE_DIRS})

add_executable(test_${PROJECT_NAME} ${ACT_SOURCES_TEST})
target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME} aft aunit)
