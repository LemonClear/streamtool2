## Core
if (USE_CORE)
        add_subdirectory (core)
endif (USE_CORE)

## NoC
if (USE_NOC)
        add_subdirectory (noc)
endif (USE_NOC)

## PCIE
if (USE_PCIE)
        add_subdirectory (pcie)
endif (USE_PCIE)

## SDRAM
if (USE_SDRAM)
        add_subdirectory (sdram)
endif (USE_SDRAM)
