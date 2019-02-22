##FP16 Table
if (USE_FP16)
        add_subdirectory (maketable)
        set (EXTRA_LIBS ${EXTRA_LIBS} maketable)
endif (USE_FP16)

##FP32 Table
if (USE_FP32)
        add_subdirectory (maketable)
        set (EXTRA_LIBS ${EXTRA_LIBS} maketable)
endif (USE_FP32)
