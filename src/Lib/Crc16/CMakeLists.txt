include_directories(
        ..
)

set( LIB_NAME Lib_crc16 )
file( GLOB SRC_FILES "*.cpp")
file( GLOB INC_FILES "*.h")
ADD_LIBRARY(${LIB_NAME} ${SRC_FILES} ${INC_FILES})