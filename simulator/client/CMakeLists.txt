########################################################
############ Add Header-Directories ####################
########################################################

# add the binary tree directory to the search path for
# include files.
include_directories (
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

########################################################
############ Add Local-Source Code #####################
########################################################

# source code.
AUX_SOURCE_DIRECTORY (. DIR_SRCS)

########################################################
############ Generate Executive or Libraries ###########
########################################################

# compose library.
add_library (client SHARED ${DIR_SRCS})

########################################################
############ Installation Things  ######################
########################################################

# install.
install (TARGETS client DESTINATION lib)
install (FILES client.h DESTINATION include)
