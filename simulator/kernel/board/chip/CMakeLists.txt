## ADD HEADER-DIRECTORIES
# add the binary tree directory to the search path for
# include files.
include_directories (
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)


## ADD SUB-DIRECTORIES
# core
if (USE_CORE)
        add_subdirectory (core)
        set (EXTRA_LIBS ${EXTRA_LIBS} core CACHE INTERNAL "Libraries.")
endif(USE_CORE)


## ADD LOCAL-SOURCE CODE
# source code
aux_source_directory (. DIR_SRCS)


## GENERATE EXECUTIVE OR LIBRARIES
# compose binary
add_library(chip STATIC ${DIR_SRCS})
add_dependencies (chip core)
