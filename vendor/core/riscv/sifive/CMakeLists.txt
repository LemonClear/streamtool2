## Si32
option (USE_SI32 "USE SI32." ON)
if (USE_SI32)
        add_subdirectory (si32)
endif (USE_SI32)

## Si64
option (USE_SI64 "USE SI64." OFF)
if (USE_SI64)
        add_subdirectory (si64)
endif (USE_SI64)
