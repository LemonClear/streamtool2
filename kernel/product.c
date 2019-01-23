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
 * global variants
 * @global_state:    the whole product run state-machine
 * @tick_counter:    the tick counts from the beginning
 * @step_counter:    the step counts from the beginning
 * @all_step_done:   all step process ok
 * @step_enable:     one step done, process another step
 *
 */
enum state global_state = OFF;
u64 tick_counter = 0;
u64 step_counter = 0;
int all_step_done = 0;
int step_enable = 0;


/**
 * __on - product power on
 * @product:   product pointer
 *
 */
static int __on(ip *product)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("--- PRODUCT %s POWER ON GO... ---\n", product->name);

        /*product level do 1st*/
        //FIXME: todo...

        /*product have no subip*/
        if (unlikely(!product->subips)) {
                ERROR("product->subips is null !!!\n");
                goto ret_on;
        }

        /*power on subips 2nd*/
        while (product->subips[id]) {
                /*each subip*/
                ret = product->subips[id]->ops->poweron(product->subips[id]);
                if (unlikely(ret)) {
                        ERROR("poweron subip%d-%s failed !!!\n",
                                        id, product->subips[id]->name);
                        goto ret_on;
                }
                /*next subip*/
                id++;
        }

        /*change state machine 3rd*/
        product->status = RUN;

        /*end*/
        INFO("--- PRODUCT %s POWER ON DONE ---\n", product->name);

ret_on:
        return ret;
}


/**
 * __off - product power off
 * @product:   product pointer
 *
 */
static int __off(ip *product)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("--- PRODUCT %s POWER OFF GO... ---\n", product->name);

        /*product have no subip*/
        if (unlikely(!product->subips)) {
                ERROR("product->subips is null !!!\n");
                goto ret_off;
        }

        /*power off subips 1st*/
        while (product->subips[id]) {
                /*each subip*/
                ret = product->subips[id]->ops->poweroff(product->subips[id]);
                if (unlikely(ret)) {
                        ERROR("poweroff subip%d-%s failed !!!\n",
                                        id, product->subips[id]->name);
                        goto ret_off;
                }
                /*next subip*/
                id++;
        }

        /*product level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        product->status = OFF;

        /*end*/
        INFO("--- PRODUCT %s POWER OFF DONE ---\n", product->name);

ret_off:
        return ret;
}


/**
 * __idle - product idle
 * @product:   product pointer
 *
 */
static int __idle(ip *product)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("--- PRODUCT %s IDLE GO... ---\n", product->name);

        /*product have no subip*/
        if (unlikely(!product->subips)) {
                ERROR("product->subips is null !!!\n");
                goto ret_idle;
        }

        /*idle subips 1st*/
        while (product->subips[id]) {
                /*each subip*/
                ret = product->subips[id]->ops->idle(product->subips[id]);
                if (unlikely(ret)) {
                        ERROR("idle subip%d-%s failed !!!\n",
                                        id, product->subips[id]->name);
                        goto ret_idle;
                }
                /*next subip*/
                id++;
        }

        /*product level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        product->status = IDLE;

        /*end*/
        INFO("--- PRODUCT %s IDLE DONE ---\n", product->name);

ret_idle:
        return ret;
}


/**
 * __sleep - product sleep
 * @product: product pointer
 *
 */
static int __sleep(ip *product)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("--- PRODUCT %s SLEEP GO... ---\n", product->name);

        /*product have no subip*/
        if (unlikely(!product->subips)) {
                ERROR("product->subips is null !!!\n");
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        while (product->subips[id]) {
                /*each subip*/
                ret = product->subips[id]->ops->sleep(product->subips[id]);
                if (unlikely(ret)) {
                        ERROR("sleep subip%d-%s failed !!!\n",
                                        id, product->subips[id]->name);
                        goto ret_sleep;
                }
                /*next subip*/
                id++;
        }

        /*product level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        product->status = SLEEP;

        /*end*/
        INFO("--- PRODUCT %s SLEEP DONE... ---\n", product->name);

ret_sleep:
        return ret;
}


/**
 * __wakeup - product wakeup
 * @product:   product pointer
 *
 */
static int __wakeup(ip *product)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("--- PRODUCT %s WAKEUP GO... ---\n", product->name);

        /*product level do 1st*/
        //FIXME: todo...

        /*product have no subip*/
        if (unlikely(!product->subips)) {
                ERROR("product->subips is null !!!\n");
                goto ret_wakeup;
        }

        /*wakeup subips 2nd*/
        while (product->subips[id]) {
                /*each subip*/
                ret = product->subips[id]->ops->wakeup(product->subips[id]);
                if (unlikely(ret)) {
                        ERROR("wakeup subip%d-%s failed !!!\n",
                                        id, product->subips[id]->name);
                        goto ret_wakeup;
                }
                /*next subip*/
                id++;
        }

        /*change state machine 3rd*/
        product->status = RUN;

        /*end*/
        INFO("--- PRODUCT %s WAKEUP DONE ---\n", product->name);

ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @product:   self pointer
 *
 */
static int __tick(ip *product)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("--- PRODUCT %s TICK:%llu GO... ---\n",
                        product->name, tick_counter);

        /*product level do 1st*/
        //FIXME: todo...

        /*product have no subip*/
        if (unlikely(!product->subips)) {
                ERROR("product->subips is null !!!\n");
                goto ret_tick;
        }

        /*tick trigger subips 2nd*/
        while (product->subips[id]) {
                /*each subip*/
                ret = product->subips[id]->ops->tickarrive(product->subips[id]);
                if (unlikely(ret)) {
                        ERROR("tick subip%d-%s failed !!!\n",
                                        id, product->subips[id]->name);
                        goto ret_tick;
                }
                /*next subip*/
                id++;
        }

        /*done*/
        INFO("--- PRODUCT %s TICK:%llu DONE ---\n",
                        product->name, tick_counter);

ret_tick:
        return ret;
}


/**
 * __dump - product dump informations
 * @product:   product pointer
 *
 */
static int __dump(ip *product)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP PRODUCT %s BEGIN ---\n", product->name);

        /*dump product elements 1st*/
        //FIXME: todo...

        /*product have no subip*/
        if (unlikely(!product->subips)) {
                ERROR("product->subips is null !!!\n");
                goto ret_dump;
        }

        /*dump subips 2nd*/
        while (product->subips[id]) {
                /*each subip*/
                ret = product->subips[id]->ops->dump(product->subips[id]);
                if (unlikely(ret)) {
                        ERROR("dump subip%d-%s failed !!!\n",
                                        id, product->subips[id]->name);
                        goto ret_dump;
                }
                /*next subip*/
                id++;
        }

        /*end*/
        DEBUG("--- DUMP PRODUCT %s END ---\n", product->name);

ret_dump:
        return ret;
}


/**
 * ops structure
 *
 */
static const ip_operations product_ops = {
        .poweron = __on,
        .poweroff = __off,
        .idle = __idle,
        .sleep = __sleep,
        .wakeup = __wakeup,
        .tickarrive = __tick,
        .dump = __dump,
};


/**
 * parse_regconfig - parse reg config file xxx.reg
 * @reglist:   pointer to reglist
 *
 * FIXME: to be replace by dt
 */
static int parse_regconfig(regs **reglist)
{
        int ret = -1;
        char *config = "./product.reg";

        if (unlikely(!reglist)) {
                ERROR("reglist is null !!!\n");
                goto ret_config;
        }

        /*begin*/
        if (unlikely(access(config, F_OK))) {
                WARNNING("config file {%s} not exist !!! use default config !!!\n",
                                config);
                ret = 0;
                goto ret_config;
        }

        //FIXME: todo...

ret_config:
        return ret;
}


/**
 * product_alloc - alloc product elements
 * @product:   pointer to product
 * @params:    init parameters
 *
 */
static int product_alloc(ip *product, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO NEED on product level!!!

        /*reg list*/
        if (!params->product_reg_count) {
                WARNNING("have no registers !!!\n");
        }

        //Trick: malloc(0)!=NULL
        product->reglist = malloc((params->product_reg_count + 1) * sizeof(regs *));
        if (unlikely(!product->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)product->reglist, 0, (params->product_reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->product_reg_count; id++) {
                product->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!product->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)product->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        product->name2reg = init_hashtable();
        if (unlikely(!product->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        product->addr2reg = init_hashtable();
        if (unlikely(!product->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
                goto ret_alloc;
        }

        /*subips list*/
        product->subips = malloc((params->board_count +
                                params->boardlink_count + 1) * sizeof(ip *));
        if (unlikely(!product->subips)) {
                ERROR("alloc subip array failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)product->subips, 0, (params->board_count +
                                params->boardlink_count + 1) * sizeof(ip *));

        for (id = 0; id < (params->board_count +
                                params->boardlink_count); id++) {
                product->subips[id] = malloc(sizeof(ip));
                if (unlikely(!product->subips[id])) {
                        ERROR("alloc subip%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)product->subips[id], 0, sizeof(ip));
        }

        /*subips hastable*/
        product->name2subip = init_hashtable();
        if (unlikely(!product->name2subip)) {
                ERROR("alloc hashtable name2subip failed !!!\n");
                goto ret_alloc;
        }

        product->addr2subip = init_hashtable();
        if (unlikely(!product->addr2subip)) {
                ERROR("alloc hashtable addr2subip failed !!!\n");
                goto ret_alloc;
        }

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * product_init - init product with params
 * @father:    pointer to the product belongs to
 * @product:   pointer to product
 * @id:        product id
 * @params:    init parameters
 *
 */
int product_init(ip *father, ip *product, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        INFO("--- PRODUCT INIT GO... ---\n");

        if (unlikely(!product) || unlikely(!params)) {
                ERROR("product is %p, params is %p !!!\n",
                                product, params);
                goto ret_init;
        }

        /*alloc*/
        ret = product_alloc(product, params);
        if (unlikely(ret)) {
                ERROR("product alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(product->name, "product%d", id);

        /*id*/
        product->id = id;

        /*state machine*/
        product->status = OFF;

        /*ops*/
        product->ops = &product_ops;

        /*memory*/
        //NO need on product level!!!

        /*reg list*/
        ret = parse_regconfig(product->reglist);
        if (unlikely(ret)) {
                ERROR("product reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->product_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(product->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(product->reglist[sub]->name,
                                (void *)product->reglist[sub],
                                product->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash reg%d:%s to name2reg failed !!!\n",
                                        sub, product->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", product->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)product->reglist[sub], product->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash reg%d:0x%x to addr2reg failed !!!\n",
                                        sub, product->reglist[sub]->address);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        product->address = product->reglist;

        /*parent*/
        product->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        for (sub = 0; sub < params->board_count; sub++) {
                /*call subip:board init function*/
                ret = board_init(product, product->subips[sub], sub, params);
                if (unlikely(ret)) {
                        ERROR("board%d init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: boardlink 2nd*/
        for (; sub < (params->board_count + params->boardlink_count); sub++) {
                /*call subip:boardlink init function*/
                ret = boardlink_init(product, product->subips[sub], sub, params);
                if (unlikely(ret)) {
                        ERROR("boardlink%d init failed !!!\n", sub);
                        goto ret_init;
                }
        }

        /*subips: hashtable*/
        for (sub = 0; sub < (params->board_count +
                                params->boardlink_count); sub++) {
                /*bypass empty subip elements*/
                if (unlikely(!strcmp(product->subips[sub]->name, "")))
                        continue;

                /*table name2subip*/
                ret = insert_hashtable(product->subips[sub]->name,
                                (void *)product->subips[sub],
                                product->name2subip);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2subip failed !!!\n",
                                        product->subips[sub]->name);
                        goto ret_init;
                }

                /*table addr2subip*/
                sprintf(addr2str, "0x%x", product->subips[sub]->address);
                ret = insert_hashtable(addr2str, (void *)product->subips[sub],
                                product->addr2subip);
                if (unlikely(ret)) {
                        ERROR("hash 0x%x to addr2subip failed !!!\n",
                                        product->subips[sub]->address);
                        goto ret_init;
                }
        }

        /*end*/
        INFO("--- PRODUCT INIT DONE ---\n");

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

        if (unlikely(!product)) {
                ERROR("product is null !!!\n");
                goto ret_run;
        }

        /*begin*/
        INFO("--- PRODUCT %s RUN GO... ---\n", product->name);

        /*power on*/
        ret = power_on(product); //power start
        if (unlikely(ret)) {
                ERROR("%s power on failed !!!\n", product->name);
                goto ret_run;
        }

        /*state machine change state*/
        global_state = RUN;

running:
        /*run*/
        if (likely(RUN == global_state)) {
                ret = clock_run(product); //clock start
                if (unlikely(ret)) {
                        ERROR("%s clock run failed !!!\n", product->name);
                        goto ret_run;
                }
        }

        /*idle*/
        while (IDLE == global_state) {
                ret = power_idle(product); //internal clock wakeup
                if (unlikely(ret)) {
                        ERROR("%s idle failed !!!\n", product->name);
                        goto ret_run;
                }

                if (unlikely(RUN == global_state))
                        goto running;
        }

        /*sleep*/
        while (SLEEP == global_state) {
                ret = power_sleep(product); //outer clock wakeup
                if (unlikely(ret)) {
                        ERROR("%s sleep failed !!!\n", product->name);
                        goto ret_run;
                }

                if (unlikely(RUN == global_state))
                        goto running;
        }

        /*power off*/
        power_off(product);

        /*end*/
        INFO("--- PRODUCT %s RUN DONE ---\n", product->name);

ret_run:
        return ret;
}
