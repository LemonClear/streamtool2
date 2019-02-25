# add the binary tree directory to the search path for
# include files
include_directories(
        "${CMAKE_CURRENT_BINARY_DIR}"
)

# source code
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

# output
add_executable(maketable ${DIR_SRCS})
