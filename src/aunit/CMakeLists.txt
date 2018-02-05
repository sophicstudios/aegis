project(aunit)

set(AUNIT_SOURCES
    aunit.h
    aunit_assert.cpp
    aunit_assert.h
    aunit_commandlineoptions.cpp
    aunit_commandlineoptions.h
    aunit_commandlineparser.cpp
    aunit_commandlineparser.h
    aunit_consolereporter.cpp
    aunit_consolereporter.h
    aunit_describe.cpp
    aunit_describe.h
    aunit_expect.cpp
    aunit_expect.h
    aunit_fixture.cpp
    aunit_fixture.h
    aunit_fixtureregistry.cpp
    aunit_fixtureregistry.h
    aunit_reporter.cpp
    aunit_reporter.h
    aunit_stringutil.cpp
    aunit_stringutil.h
    aunit_testconfiguration.cpp
    aunit_testconfiguration.h
    aunit_testmanager.cpp
    aunit_testmanager.h
    aunit_testresult.cpp
    aunit_testresult.h
)

set(${PROJECT_NAME}_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include dirs" FORCE)

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${AUNIT_SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
