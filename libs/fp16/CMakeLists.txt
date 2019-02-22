# add the binary tree directory to the search path for
# include files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add the main library
add_library(Debugger SHARED debug.c)


# installation
install (TARGETS Debugger DESTINATION lib)
install (FILES debug.h DESTINATION include)
