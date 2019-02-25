# add the command to generate the source code
add_custom_command (
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fp32_table.h
        COMMAND maketable ${CMAKE_CURRENT_BINARY_DIR}/fp32_table.h
        DEPENDS maketable
)

# add the binary tree directory to the search path for
# include files
include_directories(
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

# add the main library
add_library(fp32 STATIC fp32.c ${CMAKE_CURRENT_BINARY_DIR}/fp32_table.h)


# installation
install (TARGETS fp32 DESTINATION lib)
install (FILES fp32.h fp32_table.h DESTINATION include)
