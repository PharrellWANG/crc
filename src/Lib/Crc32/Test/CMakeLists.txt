include_directories(../)

file( GLOB SRC_FILES "*.cpp")

message(STATUS "DEBUG: SRC_FILES is ${SRC_FILES}")
set(EXE_PREFIX "srcLib_")
FOREACH(src_file ${SRC_FILES})
    get_filename_component(MYFILE_WITH_EXT ${src_file} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" MYFILE_WITHOUT_EXT ${MYFILE_WITH_EXT})
    set(exe_name ${MYFILE_WITHOUT_EXT})
    string(CONCAT full_exe_name ${EXE_PREFIX} ${exe_name})
    add_executable(${full_exe_name} ${MYFILE_WITH_EXT})
    target_link_libraries(${full_exe_name} gtest_main Lib_crc32)
    add_test(NAME ${full_exe_name} COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/${full_exe_name})
ENDFOREACH()