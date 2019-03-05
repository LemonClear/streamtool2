## ADD HEADER-DIRECTORIES
# add the binary tree directory to the search path for
# include files.
include_directories (
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)


## ADD SUB-DIRECTORIES
# ncp
if (USE_NCP)
        add_subdirectory (ncp)
        set (EXTRA_LIBS ${EXTRA_LIBS} ncp CACHE INTERNAL "Libraries.")
endif(USE_NCP)

# tcp
if (USE_TCP)
        add_subdirectory (tcp)
        set (EXTRA_LIBS ${EXTRA_LIBS} tcp CACHE INTERNAL "Libraries.")
endif(USE_TCP)


## ADD LOCAL-SOURCE CODE
# source code
aux_source_directory (. DIR_SRCS)


## GENERATE EXECUTIVE OR LIBRARIES
# compose binary
add_library(core STATIC ${DIR_SRCS})
target_link_libraries (core ncp tcp)
add_dependencies (core ncp tcp)
