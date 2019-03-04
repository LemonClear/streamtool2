## A53
option (USE_A53 "Use A53." ON)
if (USE_A53)
        add_subdirectory (cortex_a53)
        set (EXTRA_LIBS ${EXTRA_LIBS} cortex_a53 CACHE INTERNAL "Libraries.")
endif (USE_A53)

## A73
option (USE_A73 "Use A73." OFF)
if (USE_A73)
        add_subdirectory (cortex_a73)
        set (EXTRA_LIBS ${EXTRA_LIBS} cortex_a73 CACHE INTERNAL "Libraries.")
endif (USE_A73)
