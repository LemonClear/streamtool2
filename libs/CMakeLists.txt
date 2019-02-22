##OF Config
option (USE_OF "Use Configuration File." ON)
if (USE_OF)
        add_subdirectory (of)
        set (EXTRA_LIBS ${EXTRA_LIBS} of)
endif (USE_OF)

##Memory Management
option (USE_MEM "Use Memory Management Mode." ON)
if (USE_MEM)
        add_subdirectory (memory)
        set (EXTRA_LIBS ${EXTRA_LIBS} memory)
endif (USE_MEM)

##FP16 Table
option (USE_FP16 "Use Private FP16-Table Implementation." ON)
if (USE_FP16)
        add_subdirectory (fp16)
        set (EXTRA_LIBS ${EXTRA_LIBS} fp16)
endif (USE_FP16)

##FP32 Table
option (USE_FP32 "Use Private FP32-Table Implementation." ON)
if (USE_FP32)
        add_subdirectory (fp32)
        set (EXTRA_LIBS ${EXTRA_LIBS} fp32)
endif (USE_FP32)

##Hash Table && Hash Func
option (USE_HASH "Use Private Hash-Func Implementation." ON)
if (USE_HASH)
        add_subdirectory (hash)
        set (EXTRA_LIBS ${EXTRA_LIBS} hash)
endif (USE_HASH)

##CString Func
option (USE_STRING "Use Private String-Func Implementation." ON)
if (USE_STRING)
        add_subdirectory (string)
        set (EXTRA_LIBS ${EXTRA_LIBS} string)
endif (USE_STRING)

##MathFunctions
option (USE_MATH "Use Private Math-Func Implementation." ON)
if (USE_MATH)
        add_subdirectory (mathfunc)
        set (EXTRA_LIBS ${EXTRA_LIBS} mathfunc)
endif (USE_MATH)
