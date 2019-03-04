## NoC1
option (USE_NOC1 "USE NoC1." ON)
if (USE_NOC1)
        add_subdirectory (noc1)
        set (EXTRA_LIBS ${EXTRA_LIBS} noc1 CACHE INTERNAL "Libraries.")
endif (USE_NOC1)

## NoC2
option (USE_NOC2 "USE NoC2." ON)
if (USE_NOC2)
        add_subdirectory (noc2)
        set (EXTRA_LIBS ${EXTRA_LIBS} noc2 CACHE INTERNAL "Libraries.")
endif (USE_NOC2)

## NoC3
option (USE_NOC3 "USE NoC3." ON)
if (USE_NOC3)
        add_subdirectory (noc3)
        set (EXTRA_LIBS ${EXTRA_LIBS} noc3 CACHE INTERNAL "Libraries.")
endif (USE_NOC3)

## NoC4
option (USE_NOC4 "USE NoC4." ON)
if (USE_NOC4)
        add_subdirectory (noc4)
        set (EXTRA_LIBS ${EXTRA_LIBS} noc4 CACHE INTERNAL "Libraries.")
endif (USE_NOC4)
