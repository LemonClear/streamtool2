# Header Files.
include_directories (
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Add Sub-Directories
## core
option (USE_NOC "Use Noc." ON)
option (USE_CORE "Use Core." ON)
if (USE_CORE)
        add_subdirectory (ncp)
        set (EXTRA_LIBS ${EXTRA_LIBS} ncp CACHE INTERNAL "Libraries.")
        add_subdirectory (tcp)
        set (EXTRA_LIBS ${EXTRA_LIBS} tcp CACHE INTERNAL "Libraries.")
        add_subdirectory (core)
        set (EXTRA_LIBS ${EXTRA_LIBS} core CACHE INTERNAL "Libraries.")
endif(USE_CORE)

## chip
option (USE_CHIP "Use Chip." ON)
if (USE_CHIP)
        add_subdirectory (chip)
        set (EXTRA_LIBS ${EXTRA_LIBS} chip CACHE INTERNAL "Libraries.")
endif(USE_CHIP)

## board
option (USE_SDRAM "Use Sdram." ON)
option (USE_PCIE "Use Pcie." ON)
option (USE_BOARD "Use Board." ON)
if (USE_BOARD)
        add_subdirectory (board)
        set (EXTRA_LIBS ${EXTRA_LIBS} board CACHE INTERNAL "Libraries.")
endif(USE_BOARD)

## product
option (USE_PRODUCT "Use Product." ON)
if (USE_PRODUCT)
        add_subdirectory (product)
        set (EXTRA_LIBS ${EXTRA_LIBS} product CACHE INTERNAL "Libraries.")
endif(USE_PRODUCT)

# Source Code
aux_source_directory (. DIR_SRCS)

# Compose The Executable
add_executable (simulator ${DIR_SRCS})
target_link_libraries (simulator ${EXTRA_LIBS})

# installation
install (TARGETS simulator DESTINATION bin)
