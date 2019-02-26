## maketable
option (USE_MAKETABLE "Open MAKETABLE." ON)
if (USE_MAKETABLE)

        add_subdirectory (maketable)
        set (EXTRA_LIBS ${EXTRA_LIBS} maketable)
endif (USE_MAKETABLE)
