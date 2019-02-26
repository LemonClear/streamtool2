## Core
option (USE_CORE "Open Core." ON)
if (USE_CORE)
        add_subdirectory (core)
endif (USE_CORE)

## NoC
option (USE_NOC "Open NoC." ON)
if (USE_NOC)
        add_subdirectory (noc)
endif (USE_NOC)
