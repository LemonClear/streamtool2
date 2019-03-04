## A17
option (USE_A17 "Use A17." ON)
if (USE_A17)
        add_subdirectory (cortex_a17)
        set (EXTRA_LIBS ${EXTRA_LIBS} cortex_a17 CACHE INTERNAL "Libraries.")
endif (USE_A17)

## M0
option (USE_M0 "Use M0." OFF)
if (USE_M0)
        add_subdirectory (cortex_m0)
        set (EXTRA_LIBS ${EXTRA_LIBS} cortex_m0 CACHE INTERNAL "Libraries.")
endif (USE_M0)
