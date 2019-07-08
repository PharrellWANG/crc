include_directories(
        ..
)

set( LIB_NAME Lib_crcX_vtm )
file( GLOB SRC_FILES "*.cpp")
file( GLOB INC_FILES "*.h")
ADD_LIBRARY(${LIB_NAME} ${SRC_FILES} ${INC_FILES})