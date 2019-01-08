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
#include "common.h"
#include "c2xlayer.h"
#include "cmath.h"
#include "of.h"


/**
 * global variants
 * @this_product: the whole product entrance struct
 *
 */
ip *this_product = NULL;


/**
 * parse_configs - parse the config files
 * @path:       config file path
 * @params:     parameter struct
 *
 * FIXME: to be replaced by dt
 */
static int parse_configs(char *path, param *params)
{
        int ret = -1;
        FILE *stream = NULL;

        if (unlikely(!params)) {
                printf("ERR: param struct absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_configs;
        }

        if (unlikely(!path)) {
                printf("ERR: the config file absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_configs;
        }

        /*begin*/
        //FIXME: getline();

ret_configs:
        return ret;
}


/**
 * parse_commandline - parse the commandline parameters
 * @argc:       commandline strings count
 * @argv:       commanline strings
 * @params:     parameter struct
 *
 */
static int parse_commandline(int argc, char *argv[], param *params)
{
        int ret = -1;

        if (unlikely(!params)) {
                printf("WARN: param struct absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_commandline;
        }

        if (unlikely(argc < 2) || unlikely(!argv[1])) {
                printf("WARN: no command line params, use default! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_commandline;
        }

        /*begin*/
        //FIXME:


ret_commandline:
        return ret;
}


/**
 * initialization - simulator init
 * @argc:       command line parameter counts
 * @argv:       command line parameters
 * @params:     parameter struct
 *
 * FIXME: demo.config need to be dynamic or further no-need
 */
static int initialization(int argc, char *argv[], param *params)
{
        int ret = -1;
        char *path = "./demo.defconfig";

        /*begin*/
        printf("INFO: SIMULATOR initialization START!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        /*1.parse config files*/
        ret = parse_configs(path, params);
        if (unlikely(-1 == ret)) {
                printf("ERR: parse config file failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*2.parse command line*/
        if (unlikely(argc > 1) && unlikely(argv[1])) {
                ret = parse_commandline(argc, argv, params);
                if(unlikely(-1 == ret)) {
                        printf("WARN: ignore command line params! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                }
                ret = 0;
        }

        /*3.init product from top*/
        this_product = (ip *)malloc(sizeof(ip));
        if (!this_product) {
                printf("ERR: init product failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                ret = -1;
                goto ret_init;
        }


        /*end*/
        printf("INFO: SIMULATOR initialization END!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}


/**
 * main - the simulator MAIN entrace
 * @argc:       command line parameter counts
 * @argv:       command line parameters
 *
 */
int main(int argc, char *argv[])
{
        int ret = -1;
        param *params = NULL;

        /*begin*/
        printf("INFO: SIMULATOR execution START!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        /*simulator parameters*/
        params = (void *)malloc(sizeof(param));
        if (unlikely(!params)) {
                printf("ERR: params malloc failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main;
        }
        memset((void *)params, 0, sizeof(param));

        /*1.init*/
        ret = initialization(argc, argv, params);
        if (unlikely(-1 == ret)) {
                printf("ERR: simulator initialization failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main;
        }

        /*2.poweron*/
        c2xlayer_function(); //FIXME:
        //poweron(this_product);

        /*3.poweroff*/
        //poweroff(this_product);

        /*end*/
        printf("INFO: SIMULATOR execution END!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (params)
                free(params);

        exit(EXIT_SUCCESS);

ret_main:
        if (params)
                free(params);

        exit(EXIT_FAILURE);
}
