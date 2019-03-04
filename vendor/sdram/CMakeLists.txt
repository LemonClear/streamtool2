## DEMO
option (USE_DEMOSDRAM "USE Sdram." ON)
if (USE_DEMOSDRAM)
        add_subdirectory (demosdram)
        set (EXTRA_LIBS ${EXTRA_LIBS} sdram CACHE INTERNAL "Libraries.")
endif (USE_DEMOSDRAM)
