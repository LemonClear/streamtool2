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
 * parse_defconfigs - parse the config file
 * @params:     param struct
 *
 * FIXME: to be replaced by kconfig/kbuild
 */
static int parse_defconfigs(param *params)
{
        int ret = -1;
        FILE *stream = NULL;
        char *config = "./demo.defconfig";

        if (unlikely(!params)) {
                ERROR("param struct is null !!!\n");
                goto ret_config;
        }

        /*begin*/
        if (unlikely(access(config, F_OK))) {
                WARNING("config file {%s} not exist !!! use default config !!!\n",
                                config);
                ret = 0;
                goto ret_config;
        }

        //FIXME: getline(stream);

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
 * FIXME: demo.config need to be dynamic or further no-need
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

        /*parse: config file*/
        ret = parse_defconfigs(simulator->params);
        if (unlikely(ret)) {
                ERROR("parse config file failed !!!\n");
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
