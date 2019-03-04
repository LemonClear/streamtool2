## Arm32
option (USE_ARM32 "Use ARM32 Arch." ON)
if (USE_ARM32)
        add_subdirectory (arm32)
endif (USE_ARM32)

## Arm64
option (USE_ARM64 "Use ARM64 Arch." OFF)
if (USE_ARM64)
        add_subdirectory (arm64)
endif (USE_ARM64)
