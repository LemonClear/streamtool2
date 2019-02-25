cmake_minimum_required (VERSION 2.6)
project (simulator)

# 1.The Version Number.
set (SIMU_VERSION_MAJOR 2019)
set (SIMU_VERSION_MINOR 0)

# 2.Debug Options.
set(CMAKE_BUILE_TYPE DEBUG)
set(CMAKE_C_FLAGS_DEBUG "-g -m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g -m64 -pipe -frtti -std=c++11 -O2 -Wall -W -D_REENTRANT -fPIC")

# 3.Compile Options.
set(CMAKE_C_FLAGS "-m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIC -lpthread")
set(CMAKE_CXX_FLAGS "-m64 -pipe -frtti -std=c++11 -O2 -Wall -W -D_REENTRANT -fPIC -lpthread")

# 4.Directories.
set (OUTPUT_PATH ${PROJECT_BINARY_DIR}/out)
set (EXECUTABLE_OUTPUT_PATH ${OUTPUT_PATH}/bin)
set (LIBRARY_OUTPUT_PATH ${OUTPUT_PATH}/lib)

# 5.Lib Linkage Path.
link_directories (
        "${OUTPUT_PATH}"
)

# 6.Header Files.
include_directories (
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/compiler"
        "${PROJECT_SOURCE_DIR}/tools"
        "${PROJECT_SOURCE_DIR}/lib"
)

# 7.Configure a header file to pass some of the CMake settings to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/configs/SimulatorConfig.h.in"
        "${PROJECT_BINARY_DIR}/configs/SimulatorConfig.h"
)

# 8.Add Sub-Directories
add_subdirectory (libs)
add_subdirectory (test)
add_subdirectory (tools)
add_subdirectory (vendor)
add_subdirectory (scripts)
add_subdirectory (simulator)

# 9.Check system Functions Provides
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

# 10.Compose Executable
aux_source_directory (. DIR_SRCS)
add_executable (simulator ${DIR_SRCS})
target_link_libraries (simulator ${EXTRA_LIBS})

# 11.Add the make install targets
install (TARGETS simulator DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/SimulatorConfig.h" DESTINATION include)

# 12.Build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${SIMU_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${SIMU_VERSION_MINOR}")
include (CPack)
