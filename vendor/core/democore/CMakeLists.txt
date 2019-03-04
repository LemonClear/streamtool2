## Independent research
option (USE_SELFCORE "Use Self Core." ON)
if (USE_SELFCORE)
        add_subdirectory (selfcore)
        set (EXTRA_LIBS ${EXTRA_LIBS} selfcore CACHE INTERNAL "Libraries.")
endif (USE_SELFCORE)

## Git hub
option (USE_OTHERCORE "Use Other Core." OFF)
if (USE_OTHERCORE)
        add_subdirectory (othercore)
        set (EXTRA_LIBS ${EXTRA_LIBS} othercore CACHE INTERNAL "Libraries.")
endif (USE_OTHERCORE)
