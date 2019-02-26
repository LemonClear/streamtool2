## ARM
option (USE_ARM "USE ARM." ON)
if (USE_ARM)
        add_subdirectory (arm)
endif (USE_ARM)

## RISCV
option (USE_RISCV "USE RISCV." ON)
if (USE_RISCV)
        add_subdirectory (riscv)
endif (USE_RISCV)

## DEMO
option (USE_DEMO "USE DEMO." OFF)
if (USE_DEMO)
        add_subdirectory (demo)
endif (USE_DEMO)
