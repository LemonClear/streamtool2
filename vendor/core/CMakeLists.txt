## Core
option (USE_ARM "Open ARM." ON)
if (USE_ARM)
        add_subdirectory (arm)
endif (USE_ARM)

## NoC
option (USE_RISCV "Open RISCV." ON)
if (USE_RISCV)
        add_subdirectory (riscv)
endif (USE_RISCV)
