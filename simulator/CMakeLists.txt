# Header Files.
include_directories (
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Add Sub-Directories
option (USE_BOARD "Use BOARD." ON)
if (USE_BOARD)
        add_subdirectory (board)
        set (EXTRA_LIBS ${EXTRA_LIBS} board CACHE INTERNAL "Libraries.")
endif(USE_BOARD)

# Source Code
aux_source_directory (. DIR_SRCS)

# Compose The Executable
add_executable (simulator ${DIR_SRCS})
target_link_libraries (simulator ${EXTRA_LIBS})

# installation
install (TARGETS simulator DESTINATION bin)
