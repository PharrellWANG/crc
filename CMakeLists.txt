cmake_minimum_required(VERSION 3.14)
project(crc)

set(CMAKE_CXX_STANDARD 17)
# ================================================
# for adding google test
# ================================================
# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

include(cmake/googletest.cmake)
fetch_googletest(
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_BINARY_DIR}/googletest
)

enable_testing()
# ========================================

# ========================================
# glob a list of sub dir, then add_subdirectories for each sub dir
MACRO(SUBDIRLIST result glob_pattern)
    FILE(GLOB children RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${glob_pattern})
    #  message(STATUS "DEBUG: x=${children}")
    SET(dirlist "")
    FOREACH(child ${children})
        #    message(STATUS "DEBUG: child=${child}")
        IF(IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS_APP src/App/*)
SUBDIRLIST(SUBDIRS_LIB src/Lib/*)
SUBDIRLIST(SUBDIRS_TEST src/Lib/*/Test)

FOREACH(subdir ${SUBDIRS_APP})
    add_subdirectory(${subdir})
ENDFOREACH()
FOREACH(subdir ${SUBDIRS_LIB})
    add_subdirectory(${subdir})
ENDFOREACH()
FOREACH(subdir ${SUBDIRS_TEST})
    add_subdirectory(${subdir})
ENDFOREACH()
