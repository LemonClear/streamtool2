# src dir
set (CASE_DIR ${CASE_DIR} case)
set (DATA_DIR ${DATA_DIR} data)

##Test Config
option (USE_TEST "USE Test." ON)
if (USE_TEST)
        # add the command to generate the source code
        add_custom_command (
                OUTPUT COPY_RES
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${CASE_DIR} ${OUTPUT_PATH}/${CASE_DIR}
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${DATA_DIR} ${OUTPUT_PATH}/${DATA_DIR}
        )
        # target
        add_custom_target(CopyTask ALL DEPENDS COPY_RES)
endif (USE_TEST)
