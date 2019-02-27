# Header Files.
include_directories (
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/compiler"
        "${PROJECT_SOURCE_DIR}/tools"
        "${PROJECT_SOURCE_DIR}/lib"
)

# Add Sub-Directories
option (USE_BOARD "Use BOARD." ON)
if (USE_BOARD)
        add_subdirectory (board)
        set (EXTRA_LIBS ${EXTRA_LIBS} memory)
endif(USE_BOARD)

# Compose Executable
aux_source_directory (. DIR_SRCS)
add_executable (simulator ${DIR_SRCS})
target_link_libraries (simulator ${EXTRA_LIBS})

# Add the make install targets
install (TARGETS simulator DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/SimulatorConfig.h" DESTINATION include)
