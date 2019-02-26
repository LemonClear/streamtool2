## Arteris
option (USE_ARTERIS "USE ARTERIS." ON)
if (USE_ARTERIS)
        add_subdirectory (arteris)
endif (USE_ARTERIS)

## Demo
option (USE_DEMONOC "USE DEMO." OFF)
if (USE_DEMONOC)
        add_subdirectory (demo_noc)
endif (USE_DEMONOC)
