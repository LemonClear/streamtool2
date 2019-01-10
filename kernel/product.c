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
 * @global_state:    the whole product run state-machine
 * @tick_counter:    the tick counts from the beginning
 * @all_phase_done:  all phase process ok
 *
 */
enum state global_state = OFF;
u64 tick_counter = 0;
int all_phase_done = 0;


/**
 * poweron - product poweron
 * @product:   self pointer
 *
 */
static void poweron(ip *product)
{
        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_poweron;
        }

        //FIXME: todo...

ret_poweron:
        return;
}


/**
 * init - init product self
 * @product:   self pointer
 *
 * FIXME: to be replace by dt
 */
static int initself(ip *product)
{
        int ret = -1;
        char *config = "./product.reg";

        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_initself;
        }

        //FIXME: todo... init registers

ret_initself:
        return ret;
}


/**
 * tickon - one tick trigger
 * @product:   self pointer
 *
 */
static void tickon(ip *product)
{
        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        //FIXME: todo...

ret_tick:
        return;
}


/**
 * ops structure
 *
 */
static const ip_operations product_ops = {
        .poweron = poweron,
        .init = initself,
        .tick_arrive = tickon,
};


/**
 * product_init - init product with params
 * @product:   pointer to the product
 * @params:    init parameters
 *
 * FIXME: most inits move to self->ops->init according to dt, except ops
 */
int product_init(ip *product, param *params)
{
        int ret = -1;
        int sub = -1;

        /*begin*/
        printf("INFO: product init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        /*init ops*/
        product->ops = &product_ops;

        /*init regs*/
        ret = product->ops->init(product);
        if (unlikely(ret)) {
                printf("ERR: product init failed, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        //FIXME: todo...
        /*init submodules*/
        /*alloc*/
        product->subips = malloc(params->board_count * sizeof(ip *));
        if (unlikely(!product->subips)) {

        }
        memset((void *)product->subips, 0, params->board_count * sizeof(ip *));

        for (sub = 0; sub < params->board_count; sub++) {
                /*alloc*/
                (product->subips)[sub] = malloc(sizeof(ip));
                if (unlikely(!(product->subips)[sub])) {

                }
                memset((void *)(product->subips)[sub], 0, sizeof(ip));

                /*init*/
                ret = board_init((product->subips)[sub], params);
                if (unlikely(ret)) {

                }

                /*hash*/
        }


        printf("INFO: product init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}


/**
 * product_run - run this product
 * @product:     pointer to the product
 *
 */
int product_run(ip *product)
{
        int ret = -1;

        /*begin*/
        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_run;
        }

        /*power on*/
        ret = power_on(product); //power start
        if (unlikely(ret)) {
                printf("ERR: power on failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_run;
        }

        /*state machine change state*/
        global_state = RUN;

running:
        /*run*/
        if (likely(RUN == global_state)) {
                ret = clock_run(product); //clock start
                if (unlikely(ret)) {
                        printf("ERR: clock run failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_run;
                }
        }

        /*idle*/
        while (IDLE == global_state) {
                ret = power_idle(product); //internal clock wakeup
                if (unlikely(ret)) {
                        printf("ERR: power idle failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_run;
                }

                if (unlikely(RUN == global_state))
                        goto running;
        }

        /*sleep*/
        while (SLEEP == global_state) {
                ret = power_sleep(product); //outer clock wakeup
                if (unlikely(ret)) {
                        printf("ERR: power sleep failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_run;
                }

                if (unlikely(RUN == global_state))
                        goto running;
        }

        /*power off*/
        power_off(product);

ret_run:
        return ret;
}
