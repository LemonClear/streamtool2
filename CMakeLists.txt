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
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 5.Lib Path.
link_directories ("${PROJECT_BINARY_DIR}/lib")

# 6.Header Files.
include_directories (
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/compiler"
)

# 7.Configure a header file to pass some of the CMake settings to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/configs/SimulatorConfig.h.in"
        "${PROJECT_BINARY_DIR}/configs/SimulatorConfig.h"
)

# 8.Key Macros definitions shared between cmake && source code
## Debugger
option (USE_DEBUGGER
        "Open Debugger." ON)
## Logger
option (USE_LOGGER
        "Use Self Logger Implementation." ON)
## Config
option (USE_OF
        "Use Configuration File." ON)
## Memory
option (USE_MEM
        "Use Memory Management Mode." ON)
## Math
option (USE_FP16
        "Use Private FP16-Table Implementation." ON)
option (USE_FP32
        "Use Private FP32-Table Implementation." ON)
option (USE_HASH
        "Use Private Hash-Func Implementation." ON)
option (USE_STRING
        "Use Private String-Func Implementation." ON)
option (USE_MATH
        "Use Private Math-Func Implementation." ON)

# 9.Add Sub-Directories
##Debugger
if (USE_DEBUGGER)
        include_directories ("${PROJECT_SOURCE_DIR}/tools/debugger")
        add_subdirectory (debugger)
        set (EXTRA_LIBS ${EXTRA_LIBS} debugger)
endif (USE_DEBUGGER)
##Logger
if (USE_LOGGER)
        include_directories ("${PROJECT_SOURCE_DIR}/tools/logger")
        add_subdirectory (logger)
        set (EXTRA_LIBS ${EXTRA_LIBS} logger)
endif (USE_LOGGER)
##OF Config
if (USE_OF)
        include_directories ("${PROJECT_SOURCE_DIR}/lib/of")
        add_subdirectory (of)
        set (EXTRA_LIBS ${EXTRA_LIBS} of)
endif (USE_OF)
##Memory Management
if (USE_MEM)
        include_directories ("${PROJECT_SOURCE_DIR}/lib/memory")
        add_subdirectory (memory)
        set (EXTRA_LIBS ${EXTRA_LIBS} memory)
endif (USE_MEM)
##FP16 Table
if (USE_FP16)
        include_directories ("${PROJECT_SOURCE_DIR}/lib/fp16")
        add_subdirectory (fp16)
        set (EXTRA_LIBS ${EXTRA_LIBS} fp16)
endif (USE_FP16)
##FP32 Table
if (USE_FP32)
        include_directories ("${PROJECT_SOURCE_DIR}/lib/fp32")
        add_subdirectory (fp32)
        set (EXTRA_LIBS ${EXTRA_LIBS} fp32)
endif (USE_FP32)
##Hash Table && Hash Func
if (USE_HASH)
        include_directories ("${PROJECT_SOURCE_DIR}/lib/hash")
        add_subdirectory (hash)
        set (EXTRA_LIBS ${EXTRA_LIBS} hash)
endif (USE_HASH)
##CString Func
if (USE_STRING)
        include_directories ("${PROJECT_SOURCE_DIR}/lib/string")
        add_subdirectory (string)
        set (EXTRA_LIBS ${EXTRA_LIBS} string)
endif (USE_STRING)
##MathFunctions
if (USE_MATH)
        include_directories ("${PROJECT_SOURCE_DIR}/lib/mathfunc")
        add_subdirectory (mathfunc)
        set (EXTRA_LIBS ${EXTRA_LIBS} mathfunc)
endif (USE_MATH)

# 10.Check system Functions Provides
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

# 11.Compose Executable
aux_source_directory (. DIR_SRCS)
add_executable (simulator ${DIR_SRCS})
target_link_libraries (simulator ${EXTRA_LIBS})

# 12.Add the make install targets
install (TARGETS simulator DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/SimulatorConfig.h" DESTINATION include)

# 13.Build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${SIMU_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${SIMU_VERSION_MINOR}")
include (CPack)
