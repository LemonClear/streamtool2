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
option (USE_DEMOCORE "USE DEMO." OFF)
if (USE_DEMOCORE)
        add_subdirectory (demo_core)
endif (USE_DEMOCORE)
