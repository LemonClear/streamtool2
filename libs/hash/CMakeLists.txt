# add the binary tree directory to the search path for
# include files
include_directories(
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

# add the main library
add_library(hashtable STATIC hashtable.c)


# installation
install (TARGETS hashtable DESTINATION lib)
install (FILES hashtable.h DESTINATION include)
