include_directories(
        ../../Lib
)
set( EXE_NAME crc8 )
file( GLOB SRC_FILES "*.cpp" )
file( GLOB INC_FILES "*.h" )
add_executable(${EXE_NAME} ${SRC_FILES} ${INC_FILES})
target_link_libraries(${EXE_NAME} Lib_crc8)