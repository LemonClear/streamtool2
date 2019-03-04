## CADENCE
option (USE_CADENCE "USE Cadence." ON)
if (USE_CADENCE)
        add_subdirectory (cadence)
        set (EXTRA_LIBS ${EXTRA_LIBS} pcie CACHE INTERNAL "Libraries.")
endif (USE_CADENCE)

## SYNOPSIS
option (USE_SYNOPSIS "USE Synopsis." OFF)
if (USE_SYNOPSIS)
        add_subdirectory (synopsis)
        set (EXTRA_LIBS ${EXTRA_LIBS} pcie CACHE INTERNAL "Libraries.")
endif (USE_SYNOPSIS)
