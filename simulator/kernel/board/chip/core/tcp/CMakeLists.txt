## ADD HEADER-DIRECTORIES
# add the binary tree directory to the search path for
# include files.
include_directories (
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)


## ADD LOCAL-SOURCE CODE
# source code
aux_source_directory (. DIR_SRCS)


## GENERATE EXECUTIVE OR LIBRARIES
# compose binary
add_library(tcp STATIC ${DIR_SRCS})
