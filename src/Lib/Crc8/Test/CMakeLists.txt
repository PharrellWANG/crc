include_directories(../)

#set( EXE_NAME_0001 test_LeetCode_260_SingleNumberIII )
#add_executable(${EXE_NAME_0001}
#        TestID260SingleNumberIII.cpp)
#target_link_libraries(${EXE_NAME_0001} gtest_main LibBattleground)
#add_test(NAME ${EXE_NAME_0001} COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/${EXE_NAME_0001})


file( GLOB SRC_FILES "*.cpp")

message(STATUS "DEBUG: SRC_FILES is ${SRC_FILES}")
set(EXE_PREFIX "srcLibCrc8_")
FOREACH(src_file ${SRC_FILES})
    #  message(STATUS "DEBUG: src_file is ${src_file}")
    get_filename_component(MYFILE_WITH_EXT ${src_file} NAME)
    #  message(STATUS "DEBUG: MYFILE_WITH_EXT is ${MYFILE_WITH_EXT}")
    string(REGEX REPLACE "\\.[^.]*$" "" MYFILE_WITHOUT_EXT ${MYFILE_WITH_EXT})
    #  message(STATUS "DEBUG: MYFILE_WITHOUT_EXT is ${MYFILE_WITHOUT_EXT}")
    set(exe_name ${MYFILE_WITHOUT_EXT})

    string(CONCAT full_exe_name ${EXE_PREFIX} ${exe_name})
    add_executable(${full_exe_name} ${MYFILE_WITH_EXT})
    target_link_libraries(${full_exe_name} gtest_main Lib_crc8)
    add_test(NAME ${full_exe_name} COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/${full_exe_name})
ENDFOREACH()