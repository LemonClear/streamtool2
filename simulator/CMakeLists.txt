## Add HEADER-DIRECTORIES
# add the binary tree directory to the search path for
# include files.
include_directories (
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)


## Add SUB-DIRECTORIES
# distributed model.
if (USE_DISTRIBUTED)
        add_subdirectory (client)
        add_subdirectory (server)
        set (EXTRA_LIBS ${EXTRA_LIBS} client server CACHE INTERNAL "Libraries.")
endif (USE_DISTRIBUTED)
# kernel.
if (USE_KERNEL)
        add_subdirectory (kernel)
        set (EXTRA_LIBS ${EXTRA_LIBS} kernel CACHE INTERNAL "Libraries.")
endif (USE_KERNEL)


## ADD LOCAL-SOURCE CODE
# source code.
aux_source_directory (. DIR_SRCS)


## GENERATE EXECUTIVE OR LIBRARIES
# compose binary.
add_executable (simulator ${DIR_SRCS})
target_link_libraries (simulator ${EXTRA_LIBS})


## INSTALLATION THINGS
# install binary.
install (TARGETS simulator DESTINATION bin)
# install header.
install (FILES simulator.h DESTINATION include)
