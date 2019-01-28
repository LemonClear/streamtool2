/*
#
# Copyright LemonClear
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "compiler.h"
#include "logger.h"
#include "common.h" /*FIXME: to be removed*/


/**
 * of_defconfig - parse xxxx_defconfig
 * @path:       defconfig file path
 * @params:     param struct
 *
 */
int of_defconfig(const char *path, param *params)
{
        int ret = -1;

        FILE *stream = NULL;
        char *line = NULL;
        size_t len = 0;
        ssize_t nread = 0;

        char *ptr = NULL;
        char delimit = '=';

        /*begin*/
        if (unlikely(!params)) {
                ERROR("param struct is null !!!\n");
                goto ret_defconfig;
        }

        if (unlikely(!path)) {
                ERROR("path is null !!!\n");
                goto ret_defconfig;
        }

        if (unlikely(access(path, F_OK))) {
                ERROR("defconfig file {%s} not exist !!!\n", path);
                goto ret_defconfig;
        }

        /*open*/
        stream = fopen(path, "r");
        if (unlikely(!stream)) {
                ERROR("fopen file {%s} failed !!!\n", path);
                goto ret_defconfig;
        }

        /*parse each line*/
        while (-1 != (nread = getline(&line, &len, stream))) {
                /*bypass '#' lines*/
                if (unlikely('#' == *line)) continue;

                /*the position of value start is '=' + 1*/
                ptr = strchr(line, delimit) + 1;

                /*product*/
                if (strstr(line, "PRODUCT_REG_COUNT")) {
                        params->product_reg_count = atol(ptr);
                /*boardlink*/
                } else if (strstr(line, "BOARDLINK_COUNT")) {
                        params->boardlink_count = atol(ptr);
                } else if (strstr(line, "BOARDLINK_REG_COUNT")) {
                        params->boardlink_reg_count = atol(ptr);
                /*board*/
                } else if (strstr(line, "BOARD_COUNT")) {
                        params->board_count = atol(ptr);
                } else if (strstr(line, "BOARD_REG_COUNT")) {
                        params->board_reg_count = atol(ptr);
                /*chiplink*/
                } else if (strstr(line, "CHIPLINK_COUNT")) {
                        params->chiplink_count = atol(ptr);
                } else if (strstr(line, "CHIPLINK_REG_COUNT")) {
                        params->chiplink_reg_count = atol(ptr);
                /*chip*/
                } else if (strstr(line, "CHIP_COUNT")) {
                        params->chip_count = atol(ptr);
                } else if (strstr(line, "CHIP_REG_COUNT")) {
                        params->chip_reg_count = atol(ptr);
                /*ddr*/
                } else if (strstr(line, "DDR_COUNT")) {
                        params->ddr_count = atol(ptr);
                } else if (strstr(line, "DDR_REG_COUNT")) {
                        params->ddr_reg_count = atol(ptr);
                } else if (strstr(line, "DDR_SIZE")) {
                        params->ddr_size = atol(ptr);
                /*fifo*/
                } else if (strstr(line, "FIFO_COUNT")) {
                        params->fifo_count = atol(ptr);
                } else if (strstr(line, "FIFO_REG_COUNT")) {
                        params->fifo_reg_count = atol(ptr);
                } else if (strstr(line, "FIFO_SIZE")) {
                        params->fifo_size = atol(ptr);
                /*pcie*/
                } else if (strstr(line, "PCIE_COUNT")) {
                        params->pcie_count = atol(ptr);
                } else if (strstr(line, "PCIE_REG_COUNT")) {
                        params->pcie_reg_count = atol(ptr);
                /*main cpu*/
                } else if (strstr(line, "MAINCPU_COUNT")) {
                        params->maincpu_count = atol(ptr);
                } else if (strstr(line, "MAINCPU_REG_COUNT")) {
                        params->maincpu_reg_count = atol(ptr);
                /*noc*/
                } else if (strstr(line, "NOC_COUNT")) {
                        params->noc_count = atol(ptr);
                } else if (strstr(line, "NOC_REG_COUNT")) {
                        params->noc_reg_count = atol(ptr);
                /*core*/
                } else if (strstr(line, "CORE_COUNT")) {
                        params->core_count = atol(ptr);
                } else if (strstr(line, "CORE_REG_COUNT")) {
                        params->core_reg_count = atol(ptr);
                /*mcu*/
                } else if (strstr(line, "MCU_COUNT")) {
                        params->mcu_count = atol(ptr);
                } else if (strstr(line, "MCU_REG_COUNT")) {
                        params->mcu_reg_count = atol(ptr);
                /*ncp*/
                } else if (strstr(line, "NCP_COUNT")) {
                        params->ncp_count = atol(ptr);
                } else if (strstr(line, "NCP_REG_COUNT")) {
                        params->ncp_reg_count = atol(ptr);
                /*tcp*/
                } else if (strstr(line, "TCP_COUNT")) {
                        params->tcp_count = atol(ptr);
                } else if (strstr(line, "TCP_REG_COUNT")) {
                        params->tcp_reg_count = atol(ptr);
                /*ram*/
                } else if (strstr(line, "RAM_COUNT")) {
                        params->ram_count = atol(ptr);
                } else if (strstr(line, "RAM_REG_COUNT")) {
                        params->ram_reg_count = atol(ptr);
                } else if (strstr(line, "RAM_SIZE")) {
                        params->ram_size = atol(ptr);
                } else {
                        WARNING("unknown type !!!\n");
                }
        }

        /*close*/
        ret = fclose(stream);
        if (unlikely(ret)) {
                WARNING("close file {%s} failed !!!\n", path);
                goto ret_defconfig;
        }

ret_defconfig:
        return ret;
}
