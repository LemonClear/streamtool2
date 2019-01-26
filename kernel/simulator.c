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
#include "common.h"
#include "of.h"
#include "logger.h"


/**
 * parse_defconfigs - parse the defconfig file
 * @params:     param struct
 *
 * FIXME: to be replaced by kconfig/kbuild
 */
static int parse_defconfigs(param *params)
{
        int ret = -1;
        char *defconfig = "./configs/simu_defconfig";

        FILE *stream = NULL;
        char *line = NULL;
        size_t len = 0;
        ssize_t nread = 0;

        char *ptr = NULL;
        char ch = '=';

        if (unlikely(!params)) {
                ERROR("param struct is null !!!\n");
                goto ret_config;
        }

        /*begin*/
        if (unlikely(access(defconfig, F_OK))) {
                ERROR("defconfig file {%s} not exist !!!\n", defconfig);
                goto ret_config;
        }

        /*open*/
        stream = fopen(defconfig, "r");
        if (unlikely(!stream)) {
                ERROR("fopen file {%s} failed !!!\n", defconfig);
                goto ret_config;
        }

        /*parse each line*/
        while (-1 != (nread = getline(&line, &len, stream))) {
                /*bypass '#' lines*/
                if (unlikely('#' == *line)) continue;

                /*the position of value start is '=' + 1*/
                ptr = strchr(line, ch) + 1;

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
                        params->ddr_size = malloc(params->ddr_count);
                } else if (strstr(line, "DDR_REG_COUNT")) {
                        params->ddr_reg_count = atol(ptr);
                } else if (strstr(line, "DDR0_SIZE")) {
                        params->ddr_size[0] = atol(ptr);
                } else if (strstr(line, "DDR1_SIZE")) {
                        params->ddr_size[1] = atol(ptr);
                /*fifo*/
                } else if (strstr(line, "FIFO_COUNT")) {
                        params->fifo_count = atol(ptr);
                        params->fifo_size = malloc(params->fifo_count);
                } else if (strstr(line, "FIFO_REG_COUNT")) {
                        params->fifo_reg_count = atol(ptr);
                } else if (strstr(line, "FIFO0_SIZE")) {
                        params->fifo_size[0] = atol(ptr);
                } else if (strstr(line, "FIFO1_SIZE")) {
                        params->fifo_size[1] = atol(ptr);
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
                        params->ram_size = malloc(params->ram_count);
                } else if (strstr(line, "RAM_REG_COUNT")) {
                        params->ram_reg_count = atol(ptr);
                } else if (strstr(line, "RAM0_SIZE")) {
                        params->ram_size[0] = atol(ptr);
                } else if (strstr(line, "RAM1_SIZE")) {
                        params->ram_size[1] = atol(ptr);
                } else if (strstr(line, "RAM2_SIZE")) {
                        params->ram_size[2] = atol(ptr);
                } else if (strstr(line, "RAM3_SIZE")) {
                        params->ram_size[3] = atol(ptr);
                } else if (strstr(line, "RAM4_SIZE")) {
                        params->ram_size[4] = atol(ptr);
                } else {
                        WARNING("unknown type !!!\n");
                }
        }

        /*end*/
        ret = 0;

ret_config:
        return ret;
}


/**
 * parse_commandline - parse the commandline
 * @argc:       strings count
 * @argv:       strings
 * @params:     parameter struct
 *
 */
static int parse_commandline(int argc, char *argv[], param *params)
{
        int ret = -1;

        if (unlikely(!params)) {
                ERROR("param struct is null !!!\n");
                goto ret_commands;
        }

        if (unlikely(argc < 2) || unlikely(!argv[1])) {
                WARNING("no commandline parameters !!!\n");
                ret = 0;
                goto ret_commands;
        }

        /*begin*/
        //FIXME: todo...


ret_commands:
        return ret;
}


/**
 * simu_alloc - alloc simulator memory
 *
 */
static simu * simu_alloc()
{
        simu *simulator = NULL;

        /*simu*/
        simulator = malloc(sizeof(simu));
        if (unlikely(!simulator)) {
                ERROR("malloc simulator struct failed !!!\n");
                goto ret_simu;
        }
        memset((void *)simulator, 0, sizeof(simu));

        /*param*/
        simulator->params = malloc(sizeof(param));
        if (unlikely(!simulator->params)) {
                ERROR("malloc parameter struct failed !!!\n");
                goto ret_simu;
        }
        memset((void *)(simulator->params), 0, sizeof(param));

        /*product*/
        simulator->product = malloc(sizeof(ip));
        if (unlikely(!simulator->product)) {
                ERROR("malloc product struct failed !!!\n");
                goto ret_simu;
        }
        memset((void *)(simulator->product), 0, sizeof(ip));

        return simulator;

ret_simu:
        simulator = NULL;
        return simulator;
}


/**
 * simu_init - init simulator
 * @argc: commandline parameter counts
 * @argv: commandline parameters
 * @simulator: pointer to the simulator
 *
 */
static int simu_init(int argc, char *argv[], simu *simulator)
{
        int ret = -1;

        /*begin*/
        INFO("- SIMULATOR INIT GO>>> -\n");

        if (unlikely(!simulator)) {
                ERROR("simulator struct is null !!!\n");
                goto ret_init;
        }

        /*parse: defconfig file*/
        ret = parse_defconfigs(simulator->params);
        if (unlikely(ret)) {
                ERROR("parse defconfig file failed !!!\n");
                goto ret_init;
        }

        /*parse: commandline*/
        ret = parse_commandline(argc, argv, simulator->params);
        if (unlikely(ret)) {
                WARNING("ignore commandline parameters !!!\n");
        }

        /*init: the product0*/
        ret = product_init(NULL, simulator->product, 0, simulator->params);
        if (unlikely(ret)) {
                ERROR("product init failed !!!\n");
                goto ret_init;
        }

        INFO("- SIMULATOR INIT DONE -\n");

ret_init:
        return ret;
}


/**
 * simu_run - run simulator
 * @simulator:  pointer to the simulator
 *
 */
static int simu_run(simu *simulator)
{
        int ret = -1;

        /*begin*/
        INFO("- SIMULATOR RUN GO>>> -\n");

        if (unlikely(!simulator)) {
                ERROR("simulator struct is null !!!\n");
                goto ret_run;
        }

        /*run*/
        ret = product_run(simulator->product);
        if (unlikely(ret)) {
                ERROR("product run failed !!!\n");
                goto ret_run;
        }

        INFO("- SIMULATOR RUN DONE -\n");

ret_run:
        return ret;
}


/**
 * main - the simulator MAIN entrace
 * @argc:   commandline parameter counts
 * @argv:   commandline parameters
 *
 */
int main(int argc, char *argv[])
{
        int ret = -1;
        simu *simulator = NULL;

        /*begin*/
        INFO("-------- SIMULATOR EXEC START --------\n");

        /*create*/
        simulator = simu_alloc();
        if (unlikely(!simulator)) {
                ERROR("simulator create failed !!!\n");
                goto ret_main;
        }

        /*init*/
        ret = simu_init(argc, argv, simulator);
        if (unlikely(ret)) {
                ERROR("simulator init failed !!!\n");
                goto ret_main;
        }

        /*run*/
        ret = simu_run(simulator);
        if (unlikely(ret)) {
                ERROR("simulator run failed !!!\n");
                goto ret_main;
        }

        /*end*/
        INFO("-------- SIMULATOR EXEC END --------\n");

        exit(EXIT_SUCCESS);

ret_main:
        exit(EXIT_FAILURE);
}
