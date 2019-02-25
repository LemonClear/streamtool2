##Debugger
option (USE_DEBUGGER "Open Debugger." ON)
if (USE_DEBUGGER)
        add_subdirectory (debugger)
        set (EXTRA_LIBS ${EXTRA_LIBS} debugger)
endif (USE_DEBUGGER)

##Logger
option (USE_LOGGER "Use Self Logger Implementation." ON)
if (USE_LOGGER)
        add_subdirectory (logger)
        set (EXTRA_LIBS ${EXTRA_LIBS} logger)
endif (USE_LOGGER)
