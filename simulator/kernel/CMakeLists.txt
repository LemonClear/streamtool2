## ADD HEADER-DIRECTORIES
# add the binary tree directory to the search path for
# include files.
include_directories (
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)


## ADD SUB-DIRECTORIES
# board
if (USE_BOARD)
        add_subdirectory (board)
        set (EXTRA_LIBS ${EXTRA_LIBS} board CACHE INTERNAL "Libraries.")
endif (USE_BOARD)


## ADD LOCAL-SOURCE CODE
# source code
aux_source_directory (. DIR_SRCS)


## GENERATE EXECUTIVE OR LIBRARIES
# compose binary
add_library(kernel STATIC ${DIR_SRCS})
add_dependencies (kernel board)
