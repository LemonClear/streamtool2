# add the command to generate the source code
add_custom_command (
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/table.h
        COMMAND maketable ${CMAKE_CURRENT_BINARY_DIR}/table.h
        DEPENDS maketable
)

# add the binary tree directory to the search path for
# include files
include_directories(
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

# source code
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

# add the main library
add_library(mathfunc SHARED ${DIR_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/table.h)


# installation
install (TARGETS mathfunc DESTINATION lib)
install (FILES mathfunc.h DESTINATION include)
