include_directories(
        ../../Lib
)

###################################################################################
# NOTE:
# change this name when you have a new exe.
set( EXE_NAME crc8 )
###################################################################################

# get source files
file( GLOB SRC_FILES "*.cpp" )
# get include files
file( GLOB INC_FILES "*.h" )
#set( SOURCE_FILES BaseConvMain.cpp)

add_executable(${EXE_NAME} ${SRC_FILES} ${INC_FILES})
target_link_libraries(${EXE_NAME} Lib_crc8)