# first we add the executable that generates the table
add_executable(maketable maketable.c)

# add the command to generate the source code
add_custom_command (
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/table.h
        COMMAND maketable ${CMAKE_CURRENT_BINARY_DIR}/table.h
        DEPENDS maketable
)

# add the binary tree directory to the search path for
# include files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add the main library
add_library(MathFunctions STATIC mysqrt.c ${CMAKE_CURRENT_BINARY_DIR}/table.h)


# installation
install (TARGETS MathFunctions DESTINATION bin)
install (FILES mysqrt.h DESTINATION include)
