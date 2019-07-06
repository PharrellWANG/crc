include_directories(
        ..
)

# lib
set( LIB_NAME Lib_crc8 )
# get source files
file( GLOB SRC_FILES "*.cpp")
# get include files
file( GLOB INC_FILES "*.h")
#set( SOURCE_FILES BaseConvMain.cpp)

#ADD_LIBRARY(${LIB_NAME} STATIC ${SRC_FILES} ${INC_FILES})
ADD_LIBRARY(${LIB_NAME} ${SRC_FILES} ${INC_FILES})