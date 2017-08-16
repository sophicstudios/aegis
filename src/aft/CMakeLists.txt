project(aft)

################################################################################
# aftc group
################################################################################

set(AFTC_SOURCES
    aftc/aftc_construct.cpp
    aftc/aftc_construct.h
    aftc/aftc_packedstringmap.cpp
    aftc/aftc_packedstringmap.h
    aftc/aftc_trie.cpp
    aftc/aftc_trie.h
    aftc/aftc_uninitialized.h
)

set(AFTC_SOURCES_TEST
    aftc/aftc_trie.t.cpp
)

source_group(aftc FILES ${AFTC_SOURCES})

################################################################################
# aftfs group
################################################################################

set(AFTFS_SOURCES
    aftfs/aftfs_directoryentry.cpp
    aftfs/aftfs_directoryentry.h
    aftfs/aftfs_filesystem.cpp
    aftfs/aftfs_filesystem.h
    aftfs/aftfs_localfilesystem.cpp
    aftfs/aftfs_localfilesystem.h
    aftfs/aftfs_path.cpp
    aftfs/aftfs_path.h
)

set(AFTFS_SOURCES_TEST
    aftfs/aftfs_localfilesystem.t.cpp
    aftfs/aftfs_path.t.cpp
)

source_group(aftfs FILES ${AFTFS_SOURCES})

################################################################################
# afth group
################################################################################

set(AFTH_SOURCES
    afth/afth_crc32.cpp
    afth/afth_crc32.h
    afth/afth_uuid.cpp
    afth/afth_uuid.h
)

set(AFTH_SOURCES_TEST
    afth/afth_crc32.t.cpp
    afth/afth_uuid.t.cpp
)

source_group(afth FILES ${AFTH_SOURCES})

################################################################################
# aftio group
################################################################################

set(AFTIO_SOURCES
    aftio/aftio_flags.cpp
    aftio/aftio_flags.h
    aftio/aftio_permission.cpp
    aftio/aftio_permission.h
    aftio/aftio_permissions.cpp
    aftio/aftio_permissions.h
    aftio/aftio_reader.cpp
    aftio/aftio_reader.h
    aftio/aftio_writer.cpp
    aftio/aftio_writer.h
)

set(AFTIO_SOURCES_TEST)

source_group(aftio FILES ${AFTIO_SOURCES})

################################################################################
# aftipc group
################################################################################

set(AFTIPC_SOURCES
    aftipc/aftipc_mappable.cpp
    aftipc/aftipc_mappable.h
    aftipc/aftipc_mappedregion.cpp
    aftipc/aftipc_mappedregion.h
    aftipc/aftipc_memorymappedfile.cpp
    aftipc/aftipc_memorymappedfile.h
    aftipc/aftipc_resultcode.cpp
    aftipc/aftipc_resultcode.h
    aftipc/aftipc_sharedmemory.cpp
    aftipc/aftipc_sharedmemory.h
)

set(AFTIPC_SOURCES_TEST
    aftipc/aftipc_memorymappedfile.t.cpp
    aftipc/aftipc_sharedmemory.t.cpp
)

source_group(aftipc FILES ${AFTIPC_SOURCES})

################################################################################
# aftm group
################################################################################

set(AFTM_SOURCES
    aftm/aftm_round.cpp
    aftm/aftm_round.h
)

set(AFTM_SOURCES_TEST)

source_group(aftm FILES ${AFTM_SOURCES})

################################################################################
# aftma group
################################################################################

set(AFTMA_SOURCES
    aftma/aftma_allocator.cpp
    aftma/aftma_allocator.h
    aftma/aftma_blockallocator.cpp
    aftma/aftma_blockallocator.h
)

set(AFTMA_SOURCES_TEST)

source_group(aftma FILES ${AFTMA_SOURCES})

################################################################################
# afts group
################################################################################

set(AFTS_SOURCES_MSVC
    afts/afts_win32errorutil.cpp
    afts/afts_win32errorutil.h
    afts/afts_windows.cpp
    afts/afts_windows.h
)

set(AFTS_SOURCES
    afts/afts_alignmentof.cpp
    afts/afts_alignmentof.h
    afts/afts_assert.cpp
    afts/afts_assert.h
    afts/afts_byteorder.cpp
    afts/afts_byteorder.h
    afts/afts_comparisonutil.cpp
    afts/afts_comparisonutil.h
    afts/afts_compiler.cpp
    afts/afts_compiler.h
    afts/afts_errorutil.cpp
    afts/afts_errorutil.h
    afts/afts_os.cpp
    afts/afts_os.h
    afts/afts_platform.cpp
    afts/afts_platform.h
    afts/afts_stdint.h
)

set(AFTS_SOURCES_TEST
    afts/afts_comparisonutil.t.cpp
)

source_group(afts FILES ${AFTS_SOURCES})

################################################################################
# aftt group
################################################################################

set(AFTT_SOURCES
    aftt/aftt_date.cpp
    aftt/aftt_date.h
    aftt/aftt_datetime.cpp
    aftt/aftt_datetime.h
    aftt/aftt_datetimeinterval.cpp
    aftt/aftt_datetimeinterval.h
    aftt/aftt_day.cpp
    aftt/aftt_day.h
    aftt/aftt_dayofweek.cpp
    aftt/aftt_dayofweek.h
    aftt/aftt_days.cpp
    aftt/aftt_days.h
    aftt/aftt_hours.cpp
    aftt/aftt_hours.h
    aftt/aftt_microseconds.cpp
    aftt/aftt_microseconds.h
    aftt/aftt_milliseconds.cpp
    aftt/aftt_milliseconds.h
    aftt/aftt_minutes.cpp
    aftt/aftt_minutes.h
    aftt/aftt_month.cpp
    aftt/aftt_month.h
    aftt/aftt_nanoseconds.cpp
    aftt/aftt_nanoseconds.h
    aftt/aftt_seconds.cpp
    aftt/aftt_seconds.h
    aftt/aftt_systemtime.cpp
    aftt/aftt_systemtime.h
    aftt/aftt_time.cpp
    aftt/aftt_time.h
    aftt/aftt_timezone.cpp
    aftt/aftt_timezone.h
    aftt/aftt_weeks.cpp
    aftt/aftt_weeks.h
    aftt/aftt_year.cpp
    aftt/aftt_year.h
    aftt/aftt_years.cpp
    aftt/aftt_years.h
)

set(AFTT_SOURCES_TEST
    aftt/aftt_date.t.cpp
    aftt/aftt_datetime.t.cpp
    aftt/aftt_datetimeinterval.t.cpp
    aftt/aftt_time.t.cpp
)

source_group(aftt FILES ${AFTT_SOURCES})

################################################################################
# aftu group
################################################################################

set(AFTU_SOURCES_MSVC
    aftu/aftu_win32error.cpp
    aftu/aftu_win32error.h
)

set(AFTU_SOURCES
    aftu/aftu_exception.cpp
    aftu/aftu_exception.h
    aftu/aftu_hexprinter.cpp
    aftu/aftu_hexprinter.h
    aftu/aftu_hexutil.cpp
    aftu/aftu_hexutil.h
    aftu/aftu_nullable.h
    aftu/aftu_stringref.cpp
    aftu/aftu_stringref.h
    aftu/aftu_stringutil.cpp
    aftu/aftu_stringutil.h
    aftu/aftu_typedbuffer.h
    aftu/aftu_typedexception.h
    aftu/aftu_url.cpp
    aftu/aftu_url.h
)

set(AFTU_SOURCES_TEST
    aftu/aftu_hexprinter.t.cpp
    aftu/aftu_nullable.t.cpp
    aftu/aftu_stringref.t.cpp
    aftu/aftu_stringutil.t.cpp
    aftu/aftu_url.t.cpp
)

source_group(aftu   FILES ${AFTU_SOURCES})

################################################################################
# aft library
################################################################################

set(AFT_SOURCES
    ${AFTC_SOURCES}
    ${AFTFS_SOURCES}
    ${AFTH_SOURCES}
    ${AFTIO_SOURCES}
    ${AFTIPC_SOURCES}
    ${AFTM_SOURCES}
    ${AFTMA_SOURCES}
    ${AFTS_SOURCES}
    ${AFTT_SOURCES}
    ${AFTU_SOURCES}
)

set(${PROJECT_NAME}_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/aftc
    ${PROJECT_SOURCE_DIR}/aftfs
    ${PROJECT_SOURCE_DIR}/afth
    ${PROJECT_SOURCE_DIR}/aftio
    ${PROJECT_SOURCE_DIR}/aftipc
    ${PROJECT_SOURCE_DIR}/aftm
    ${PROJECT_SOURCE_DIR}/aftma
    ${PROJECT_SOURCE_DIR}/afts
    ${PROJECT_SOURCE_DIR}/aftt
    ${PROJECT_SOURCE_DIR}/aftu
    CACHE INTERNAL "${PROJECT_NAME}: Include dirs" FORCE)

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${AFT_SOURCES})

################################################################################
# aft unit tests
################################################################################

set(AFT_SOURCES_TEST
    ${AFTC_SOURCES_TEST}
    ${AFTFS_SOURCES_TEST}
    ${AFTH_SOURCES_TEST}
    ${AFTIO_SOURCES_TEST}
    ${AFTIPC_SOURCES_TEST}
    ${AFTM_SOURCES_TEST}
    ${AFTMA_SOURCES_TEST}
    ${AFTS_SOURCES_TEST}
    ${AFTT_SOURCES_TEST}
    ${AFTU_SOURCES_TEST}
    aft.t.cpp
)

include_directories(${aunit_INCLUDE_DIRS})

add_executable(test_${PROJECT_NAME} ${AFT_SOURCES_TEST})

target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME} aunit)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
