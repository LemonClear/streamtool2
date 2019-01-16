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


/**
 * parse_configs - parse the config file
 * @params:     param struct
 *
 * FIXME: to be replaced by kconfig/kbuild
 */
static int parse_configs(param *params)
{
        int ret = -1;
        FILE *stream = NULL;
        char *config = "./demo.defconfig";

        if (unlikely(!params)) {
                printf("ERR: param struct absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_config;
        }

        /*begin*/
        if (unlikely(access(config, F_OK))) {
                printf("INFO: config file %s absent! \
                                use default no reg config! %s, %s, %d\n",
                                config, __FILE__, __func__, __LINE__);
                ret = 0;
                goto ret_config;
        }

        //FIXME: getline(stream);

ret_config:
        return ret;
}


/**
 * parse_commands - parse the command line
 * @argc:       strings count
 * @argv:       strings
 * @params:     parameter struct
 *
 */
static int parse_commands(int argc, char *argv[], param *params)
{
        int ret = -1;

        if (unlikely(!params)) {
                printf("ERR: param struct absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_commands;
        }

        if (unlikely(argc < 2) || unlikely(!argv[1])) {
                printf("WARN: no command line params, use default! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
                printf("ERR: malloc simu struct failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_simu;
        }
        memset((void *)simulator, 0, sizeof(simu));

        /*param*/
        simulator->params = malloc(sizeof(param));
        if (unlikely(!simulator->params)) {
                printf("ERR: malloc param struct failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_simu;
        }
        memset((void *)(simulator->params), 0, sizeof(param));

        /*product*/
        simulator->product = malloc(sizeof(ip));
        if (unlikely(!simulator->product)) {
                printf("ERR: malloc product struct failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
 * @argc: command line parameter counts
 * @argv: command line parameters
 * @simulator: pointer to the simulator
 *
 * FIXME: demo.config need to be dynamic or further no-need
 */
static int simu_init(int argc, char *argv[], simu *simulator)
{
        int ret = -1;

        /*begin*/
        if (unlikely(!simulator)) {
                printf("ERR: simulator struct absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*parse: config file*/
        ret = parse_configs(simulator->params);
        if (unlikely(ret)) {
                printf("ERR: parse config file failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*parse: command line*/
        ret = parse_commands(argc, argv, simulator->params);
        if (unlikely(ret)) {
                printf("WARN: ignore command lines! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        /*init: the whole product*/
        ret = product_init(NULL, simulator->product, 0, simulator->params);
        if (unlikely(ret)) {
                printf("ERR: product init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

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
        if (unlikely(!simulator)) {
                printf("ERR: simulator struct absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_run;
        }

        /*run*/
        ret = product_run(simulator->product);
        if (unlikely(ret)) {
                printf("ERR: product run failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

ret_run:
        return ret;
}


/**
 * main - the simulator MAIN entrace
 * @argc:   command line parameter counts
 * @argv:   command line parameters
 *
 */
int main(int argc, char *argv[])
{
        int ret = -1;
        simu *simulator = NULL;

        /*begin*/
        printf("INFO: SIMULATOR execution START!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        /*create*/
        simulator = simu_alloc();
        if (unlikely(!simulator)) {
                printf("ERR: simulator create failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main;
        }

        /*init*/
        ret = simu_init(argc, argv, simulator);
        if (unlikely(ret)) {
                printf("ERR: simulator init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main;
        }

        /*run*/
        ret = simu_run(simulator);
        if (unlikely(ret)) {
                printf("ERR: simulator run failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main;
        }

        /*end*/
        printf("INFO: SIMULATOR execution END!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        exit(EXIT_SUCCESS);

ret_main:
        exit(EXIT_FAILURE);
}
