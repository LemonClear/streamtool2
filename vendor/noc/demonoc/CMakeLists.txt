## Independent research
option (USE_SELFNOC "Use Self NoC." ON)
if (USE_SELFNOC)
        add_subdirectory (selfnoc)
endif (USE_SELFNOC)

## Git hub
option (USE_OTHERNOC "Use Other NoC." OFF)
if (USE_OTHERNOC)
        add_subdirectory (othernoc)
endif (USE_OTHERNOC)
