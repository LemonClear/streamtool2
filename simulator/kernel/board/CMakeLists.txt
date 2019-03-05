## ADD HEADER-DIRECTORIES
# add the binary tree directory to the search path for
# include files.
include_directories (
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)


## ADD SUB-DIRECTORIES
# chip
if (USE_CHIP)
        add_subdirectory (chip)
        set (EXTRA_LIBS ${EXTRA_LIBS} chip CACHE INTERNAL "Libraries.")
endif(USE_CHIP)


## ADD LOCAL-SOURCE CODE
# source code
aux_source_directory (. DIR_SRCS)


## GENERATE EXECUTIVE OR LIBRARIES
# compose binary
add_library(board STATIC ${DIR_SRCS})
