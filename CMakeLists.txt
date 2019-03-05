## VERSION AND PROJECT SETTING
# cmake version.
cmake_minimum_required (VERSION 2.6)
# project name.
project (simulator)
# project version.
set (SIMU_VERSION_MAJOR 2019)
set (SIMU_VERSION_MINOR 0)


## COMPILE FLAGS SETTING
# debug options.
set (CMAKE_BUILE_TYPE DEBUG)
set (CMAKE_C_FLAGS_DEBUG "-g -m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIC")
set (CMAKE_CXX_FLAGS_DEBUG "-g -m64 -pipe -frtti -std=c++11 -O2 -Wall -W -D_REENTRANT -fPIC")
# normal options.
set (CMAKE_C_FLAGS "-m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIC -lpthread")
set (CMAKE_CXX_FLAGS "-m64 -pipe -frtti -std=c++11 -O2 -Wall -W -D_REENTRANT -fPIC -lpthread")


## DIRECTORY SETTING
# output bin lib dirs.
set (OUTPUT_PATH ${PROJECT_BINARY_DIR}/out)
set (EXECUTABLE_OUTPUT_PATH ${OUTPUT_PATH}/bin)
set (LIBRARY_OUTPUT_PATH ${OUTPUT_PATH}/lib)


## LINKAGE SETTING
# library to link.
set (EXTRA_LIBS "${EXTRA_LIBS}" CACHE INTERNAL "Libraries.")
# library path.
link_directories (
        "${OUTPUT_PATH}"
)
# header dirs.
include_directories (
        "${PROJECT_BINARY_DIR}/configs"
        "${PROJECT_SOURCE_DIR}/compiler"
        "${PROJECT_SOURCE_DIR}/simulator"

        "${PROJECT_SOURCE_DIR}/libs/of"
        "${PROJECT_SOURCE_DIR}/libs/hash"
        "${PROJECT_SOURCE_DIR}/libs/string"
        "${PROJECT_SOURCE_DIR}/tools/logger"
)
# speedup
set (CMAKE_DEPENDS_IN_PROJECT_ONLY ON)


## SYSTEM CHECKSOME SETTING
# if system functions provides.
#include (CheckFunctionExists)
#check_function_exists (log HAVE_LOG)
#check_function_exists (exp HAVE_EXP)


## SOC SIMULATOR OPTIONS
option (USE_DISTRIBUTED "Use Distributed Simulator Model." ON)

option (USE_KERNEL "Use Kernel." ON)
if (USE_KERNEL)
        option (USE_BOARD "Use Board." ON)
        if (USE_BOARD)
                set (BOARD_COUNT 1)
                option (USE_CHIP "Use Chip." ON)
                if (USE_CHIP)
                        set (CHIP_COUNT 2)
                        option (USE_CORE "Use Core." ON)
                        if (USE_CORE)
                                set (CORE_COUNT 768)
                                option (USE_NCP "Use NCP." ON)
                                option (USE_TCP "Use TCP." ON)
                        endif (USE_CORE)
                        option (USE_NOC "Use NoC." OFF)
                endif (USE_CHIP)
        endif (USE_BOARD)
endif (USE_KERNEL)


## TOTAL CONFIGURATION SETTING
# Configure a header file to pass some of the CMake settings to the source code.
configure_file (
        "${PROJECT_SOURCE_DIR}/configs/SimulatorConfig.h.in"
        "${PROJECT_BINARY_DIR}/configs/SimulatorConfig.h"
)


## SUB_DIRECTORIES
# attention - these sub-dirs may have dependencies
add_subdirectory (scripts)
add_subdirectory (libs)
add_subdirectory (tools)
add_subdirectory (vendor)
add_subdirectory (simulator)
add_subdirectory (test)


## INSTALLATION SETTING
# install configure_file
install (FILES "${PROJECT_BINARY_DIR}/SimulatorConfig.h" DESTINATION include)


## PROJECT PACKAGE SETTING
# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${SIMU_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${SIMU_VERSION_MINOR}")
include (CPack)
