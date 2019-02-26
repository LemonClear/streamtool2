## N25
option (USE_N25 "USE N25." ON)
if (USE_N25)
        add_subdirectory (n25)
endif (USE_N25)

## NX25
option (USE_NX25 "USE NX25." OFF)
if (USE_NX25)
        add_subdirectory (nx25)
endif (USE_NX25)
