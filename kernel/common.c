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
                printf("param struct absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_configs;
        }

        if (unlikely(!path)) {
                printf("the config file absent! %s, %s, %d\n",
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
                printf("param struct absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_commandline;
        }

        if (unlikely(argc < 2) || unlikely(!argv[1])) {
                printf("no command line params, use default! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_commandline;
        }

        /*begin*/
        //FIXME:


ret_commandline:
        return ret;
}


/**
 * initialization - the simulator MAIN entrace
 * @argc:       command line parameter counts
 * @argv:       command line parameters
 *
 */
static int initialization()
{
        int ret = -1;

ret_init:
        return ret;
}


/**
 * main - the simulator MAIN entrace
 * @argc:       command line parameter counts
 * @argv:       command line parameters
 *
 * FIXME: demo.config need to be dynamic or further no-need
 */
int main(int argc, char *argv[])
{
        int ret = -1;
        char *path = "./demo.defconfig";
        param *params = NULL;

        /*begin*/
        printf("INFO: SIMULATOR execution START!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        /*simulator config param struct*/
        params = (void *)malloc(sizeof(param));
        if (unlikely(!params)) {
                printf("params malloc failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main_err;
        }
        memset((void *)params, 0, sizeof(param));

        /*1.parse config files*/
        ret = parse_configs(path, params);
        if (unlikely(-1 == ret)) {
                printf("parse config file failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main_err;
        }

        /*2.parse command line*/
        if (unlikely(argc > 1) && unlikely(argv[1])) {
                ret = parse_commandline(argc, argv, params);
                if(unlikely(-1 == ret)) {
                        printf("ignore command line params! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                }
        }

        /*3.initialization*/
        ret = initialization();
        if (unlikely(-1 == ret)) {
                printf("simulator initialization failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main_err;
        }

        /*4.clock trigger*/
        c2xlayer_function();

        /*end*/
        printf("INFO: SIMULATOR execution END!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (params)
                free(params);

        exit(EXIT_SUCCESS);

ret_main_err:
        if (params)
                free(params);

        exit(EXIT_FAILURE);
}
