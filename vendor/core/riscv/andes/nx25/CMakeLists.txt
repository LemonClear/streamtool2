# add the binary tree directory to the search path for
# include files
include_directories(
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

# source code
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

# add the main library
add_library(nx25 SHARED ${DIR_SRCS})


# installation
install (TARGETS nx25 DESTINATION lib)
install (FILES nx25.h DESTINATION include)
