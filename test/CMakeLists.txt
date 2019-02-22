##Test Config
option (USE_TEST "USE Test." ON)
if (USE_TEST)
        add_subdirectory (test)
        add_subdirectory (data)
endif (USE_TEST)
