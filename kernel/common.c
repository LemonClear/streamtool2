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
#include "of.h"


/**
 * global variants
 * @global_state:   the whole product run state-machine
 *
 */
enum state global_state = OFF;


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
                printf("ERR: param struct absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_commandline;
        }

        if (unlikely(argc < 2) || unlikely(!argv[1])) {
                printf("WARN: no command line params, use default! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_commandline;
        }

        /*begin*/
        //FIXME: todo...


ret_commandline:
        return ret;
}


/**
 * initialization - simulator init
 * @argc:       command line parameter counts
 * @argv:       command line parameters
 *
 * FIXME: demo.config need to be dynamic or further no-need
 */
static ip * initialization(int argc, char *argv[])
{
        int ret = -1;
        char *path = "./demo.defconfig";
        param *params = NULL;
        ip *product = NULL;

        /*begin*/
        printf("INFO: SIMULATOR initialization START!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        /*alloc param struct*/
        params = (void *)malloc(sizeof(param));
        if (unlikely(!params)) {
                printf("ERR: malloc param struct failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init_err;
        }
        memset((void *)params, 0, sizeof(param));

        /*parse config files*/
        ret = parse_configs(path, params);
        if (unlikely(-1 == ret)) {
                printf("ERR: parse config file failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init_err;
        }

        /*parse command line*/
        if (unlikely(argc > 1) && unlikely(argv[1])) {
                ret = parse_commandline(argc, argv, params);
                if (unlikely(-1 == ret)) {
                        printf("WARN: ignore command lines! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                }
        }

        /*alloc product struct*/
        product = (ip *)malloc(sizeof(ip));
        if (unlikely(!product)) {
                printf("ERR: malloc product struct failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init_err;
        }
        memset((void *)product, 0, sizeof(ip));

        /*init product from top*/
        ret = product_init(product, params);
        if (unlikely(-1 == ret)) {
                printf("ERR: product init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init_err;
        }

        /*end*/
        printf("INFO: SIMULATOR initialization END!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (likely(params))
                free(params);

        return product;

ret_init_err:
        if (likely(params))
                free(params);

        if (likely(product)) {
                free(product);
                product = NULL;
        }

        return product;
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
        ip *this_product = NULL;

        /*begin*/
        printf("INFO: SIMULATOR execution START!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        /*1.product init*/
        this_product = initialization(argc, argv);
        if (unlikely(!this_product)) {
                printf("ERR: simulator initialization failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main_err;
        }

        /*2.power on*/
        ret = poweron(this_product);
        if (unlikely(-1 == ret)) {
                printf("ERR: power on failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_main_err;
        }

        global_state = RUN;

running:
        /*3.power run*/
        while (RUN == global_state) {
                ret = powerrun(this_product);
                if (unlikely(-1 == ret)) {
                        printf("ERR: power run failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_main_err;
                }
        }

        /*4.power idle*/
        while (IDLE == global_state) {
                //no clock, need clock wakeup
                ret = poweridle(this_product);
                if (unlikely(-1 == ret)) {
                        printf("ERR: power idle failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_main_err;
                }

                if (unlikely(RUN == global_state))
                        goto running;
        }

        /*5.power sleep*/
        while (SLEEP == global_state) {
                //no power no clock, need outside clock wakeup
                ret = powersleep(this_product);
                if (unlikely(-1 == ret)) {
                        printf("ERR: power sleep failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_main_err;
                }

                if (unlikely(RUN == global_state))
                        goto running;
        }

        /*6.power off*/
        poweroff(this_product);

        /*end*/
        printf("INFO: SIMULATOR execution END!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        exit(EXIT_SUCCESS);

ret_main_err:
        exit(EXIT_FAILURE);
}
