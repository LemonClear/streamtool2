# add the binary tree directory to the search path for include files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_executable(maketable ${DIR_SRCS})
