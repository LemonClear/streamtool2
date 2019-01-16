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
 * global variants
 * @global_state:    the whole product run state-machine
 * @tick_counter:    the tick counts from the beginning
 * @step_counter:    the step counts from the beginning
 * @all_step_done:   all step process ok
 *
 */
enum state global_state = OFF;
u64 tick_counter = 0;
u64 step_counter = 0;
int all_step_done = 0;


/**
 * __on - product power on
 * @product:   product pointer
 *
 */
static void __on(ip *product)
{
        int id = 0;

        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*product level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        while (product->subips[id]) {
                /*each subip*/
                product->subips[id]->ops->poweron(product->subips[id]);

                id++;
        }

        /*change state machine 3rd*/
        product->status = RUN;

        printf("INFO: product:%s power on!!!!! %s, %s, %d\n",
                        product->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * __off - product power off
 * @product:   product pointer
 *
 */
static void __off(ip *product)
{
        int id = 0;

        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        while (product->subips[id]) {
                /*each subip*/
                product->subips[id]->ops->poweroff(product->subips[id]);

                id++;
        }

        /*product level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        product->status = OFF;

        printf("INFO: product:%s power off!!!!! %s, %s, %d\n",
                        product->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * __idle - product idle
 * @product:   product pointer
 *
 */
static void __idle(ip *product)
{
        int id = 0;

        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        while (product->subips[id]) {
                /*each subip*/
                product->subips[id]->ops->idle(product->subips[id]);

                id++;
        }

        /*product level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        product->status = IDLE;

        printf("INFO: product:%s idle!!!!! %s, %s, %d\n",
                        product->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * __sleep - product sleep
 * @product:   product pointer
 *
 */
static void __sleep(ip *product)
{
        int id = 0;

        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        while (product->subips[id]) {
                /*each subip*/
                product->subips[id]->ops->sleep(product->subips[id]);

                id++;
        }

        /*product level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        product->status = SLEEP;

        printf("INFO: product:%s sleep!!!!! %s, %s, %d\n",
                        product->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * __wakeup - product wakeup
 * @product:   product pointer
 *
 */
static void __wakeup(ip *product)
{
        int id = 0;

        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*product level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        while (product->subips[id]) {
                /*each subip*/
                product->subips[id]->ops->wakeup(product->subips[id]);

                id++;
        }

        /*change state machine 3rd*/
        product->status = RUN;

        printf("INFO: product:%s wakeup!!!!! %s, %s, %d\n",
                        product->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * __tick - one tick trigger
 * @product:   self pointer
 *
 */
static void __tick(ip *product)
{
        int id = 0;

        if (unlikely(!product)) {
                printf("ERR: product absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: product:%s tick:%llu come!!!!! %s, %s, %d\n",
                        product->name, tick_counter, __FILE__, __func__, __LINE__);

        /*product level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        while (product->subips[id]) {
                /*each subip*/
                product->subips[id]->ops->tickarrive(product->subips[id]);

                id++;
        }

        /*done*/
        printf("INFO: product:%s tick:%llu done!!!!! %s, %s, %d\n",
                        product->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * __dump - product dump informations
 * @product:   product pointer
 *
 */
static void __dump(ip *product)
{
        int id = 0;

        printf("DEBUG: ========== product:%s dump start !!!!! ==========\n",
                        product->name);

        if (unlikely(!product)) {
                printf("ERR: product absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump product elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        while (product->subips[id]) {
                /*each subip*/
                product->subips[id]->ops->dump(product->subips[id]);

                id++;
        }

        printf("DEBUG: ========== product:%s dump end !!!!! ==========\n",
                        product->name);

ret_dump:
        return;
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
                printf("ERR: product reglist absent! %s, %s, %d\n",
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
        if (!params->reg_count) { //FIXME: should separate ips reg count
                printf("INFO: product have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        product->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!product->reglist)) {
                printf("ERR: alloc product reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)product->reglist, 0, (params->reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                product->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!product->reglist[id])) {
                        printf("ERR: alloc product reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)product->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        product->name2reg = init_hashtable();
        if (unlikely(!product->name2reg)) {
                printf("ERR: alloc product reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        product->addr2reg = init_hashtable();
        if (unlikely(!product->addr2reg)) {
                printf("ERR: alloc product reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        /*subips list*/
        product->subips = malloc((params->board_count +
                                params->boardlink_count + 1) * sizeof(ip *));
        if (unlikely(!product->subips)) {
                printf("ERR: product alloc subip array failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)product->subips, 0, (params->board_count +
                                params->boardlink_count + 1) * sizeof(ip *));

        for (id = 0; id < (params->board_count +
                                params->boardlink_count); id++) {
                product->subips[id] = malloc(sizeof(ip));
                if (unlikely(!product->subips[id])) {
                        printf("ERR: alloc product subip%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)product->subips[id], 0, sizeof(ip));
        }

        /*subips hastable*/
        product->name2subip = init_hashtable();
        if (unlikely(!product->name2subip)) {
                printf("ERR: alloc product subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        product->addr2subip = init_hashtable();
        if (unlikely(!product->addr2subip)) {
                printf("ERR: alloc product subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
        printf("INFO: product init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!product) || unlikely(!params)) {
                printf("ERR: product or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = product_alloc(product, params);
        if (unlikely(ret)) {
                printf("ERR: product alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
        //FIXME: DO NOTHING!!!
        //NO NEED on product level!!!

        /*reg list*/
        ret = parse_regconfig(product->reglist);
        if (unlikely(ret)) {
                printf("ERR: product reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(product->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(product->reglist[sub]->name,
                                (void *)product->reglist[sub],
                                product->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, product->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", product->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)product->reglist[sub], product->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, product->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        product->address = product->reglist;

        /*parent*/
        product->parent = father;

        /*connected*/
        product->east = NULL;
        product->west = NULL;
        product->sourth = NULL;
        product->north = NULL;

        /*subips: board 1st*/
        for (sub = 0; sub < params->board_count; sub++) {
                /*call subip:board init function*/
                ret = board_init(product, product->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: board%d init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: boardlink 2nd*/
        for (; sub < (params->board_count + params->boardlink_count); sub++) {
                /*call subip:boardlink init function*/
                ret = boardlink_init(product, product->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: boardlink%d init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
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
                        printf("ERR: hash %s to name2subip table failed! %s, %s, %d\n",
                                        product->subips[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2subip*/
                sprintf(addr2str, "0x%x", product->subips[sub]->address);
                ret = insert_hashtable(addr2str, (void *)product->subips[sub],
                                product->addr2subip);
                if (unlikely(ret)) {
                        printf("ERR: hash board/boardlink%d:0x%x to addr2subip table failed! %s, %s, %d\n",
                                        sub, product->subips[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
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
