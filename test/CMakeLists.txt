# src dir
set (CASE_DIR ${CASE_DIR} case)
set (DATA_DIR ${DATA_DIR} data)

## case and data
option (USE_CASE "USE Case and Data." ON)
if (USE_CASE)
        # add the command to generate the source code
        add_custom_command (
                OUTPUT COPY_RES
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${CASE_DIR} ${OUTPUT_PATH}/${CASE_DIR}
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${DATA_DIR} ${OUTPUT_PATH}/${DATA_DIR}
        )
        # target
        add_custom_target(CopyTask ALL DEPENDS COPY_RES)
endif (USE_CASE)

## auto test
option (USE_AUTOTEST "USE Autotest." ON)
if (USE_AUTOTEST)
        add_subdirectory (autotest)
endif (USE_AUTOTEST)
