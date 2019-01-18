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
 * @step_enable:     one step done, process another step
 *
 */
enum state global_state = OFF;
u64 tick_counter = 0;
u64 step_counter = 0;
int all_step_done = 0;
int step_enable = 0;


/**
 * this ip pointer
 *
 */
static ip *this = NULL;


/**
 * __on - ip power on
 *
 */
static int __on()
{
        int ret = -1;
        int id = 0;

        if (unlikely(!this)) {
                printf("ERR: product absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*1. power on this*/
        //FIXME: todo...

        /*have no subip*/
        if (unlikely(!this->subips)) {
                printf("ERR: %s:subips absent! %s, %s, %d\n",
                                this->name, __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*power on subips 2nd*/
        while (this->subips[id]) {
                /*each subip*/
                ret = this->subips[id]->ops->poweron(this->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: poweron subip%d-%s failed! %s, %s, %d\n",
                                        id, this->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_on;
                }
                /*next subip*/
                id++;
        }

        /*change state machine 3rd*/
        this->status = RUN;

        printf("INFO: %s power on!!! %s, %s, %d\n",
                        this->name, __FILE__, __func__, __LINE__);

ret_on:
        return ret;
}


/**
 * __off - ip power off
 *
 */
static int __off()
{
        int ret = -1;
        int id = 0;

        if (unlikely(!this)) {
                printf("ERR: product absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*have no subip*/
        if (unlikely(!this->subips)) {
                printf("ERR: %s:subips absent! %s, %s, %d\n",
                                this->name, __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*1. power off subips*/
        while (this->subips[id]) {
                /*each subip*/
                ret = this->subips[id]->ops->poweroff(this->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: poweroff subip%d-%s failed! %s, %s, %d\n",
                                        id, this->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_off;
                }
                /*next subip*/
                id++;
        }

        /*2. power off this*/
        //FIXME: todo...

        /*change state machine 3rd*/
        this->status = OFF;

        printf("INFO: %s power off!!! %s, %s, %d\n",
                        this->name, __FILE__, __func__, __LINE__);

ret_off:
        return ret;
}


/**
 * __idle - ip idle
 *
 */
static int __idle()
{
        int ret = -1;
        int id = 0;

        if (unlikely(!this)) {
                printf("ERR: product absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*have no subip*/
        if (unlikely(!this->subips)) {
                printf("ERR: %s:subips absent! %s, %s, %d\n",
                                this->name, __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*1. idle subips*/
        while (this->subips[id]) {
                /*each subip*/
                ret = this->subips[id]->ops->idle(this->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: idle subip%d-%s failed! %s, %s, %d\n",
                                        id, this->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_idle;
                }
                /*next subip*/
                id++;
        }

        /*2. idle this*/
        //FIXME: todo...

        /*change state machine 3rd*/
        this->status = IDLE;

        printf("INFO: %s idle!!! %s, %s, %d\n",
                        this->name, __FILE__, __func__, __LINE__);

ret_idle:
        return ret;
}


/**
 * __sleep - ip sleep
 *
 */
static int __sleep()
{
        int ret = -1;
        int id = 0;

        if (unlikely(!this)) {
                printf("ERR: product absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*have no subip*/
        if (unlikely(!this->subips)) {
                printf("ERR: %s:subips absent! %s, %s, %d\n",
                                this->name, __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*1. sleep subips*/
        while (this->subips[id]) {
                /*each subip*/
                ret = this->subips[id]->ops->sleep(this->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: sleep subip%d-%s failed! %s, %s, %d\n",
                                        id, this->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_sleep;
                }
                /*next subip*/
                id++;
        }

        /*2. sleep this*/
        //FIXME: todo...

        /*change state machine 3rd*/
        this->status = SLEEP;

        printf("INFO: %s sleep!!! %s, %s, %d\n",
                        this->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return ret;
}


/**
 * __wakeup - ip wakeup
 *
 */
static int __wakeup()
{
        int ret = -1;
        int id = 0;

        if (unlikely(!this)) {
                printf("ERR: product absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*1. wakeup this*/
        //FIXME: todo...

        /*have no subip*/
        if (unlikely(!this->subips)) {
                printf("ERR: %s:subips absent! %s, %s, %d\n",
                                this->name, __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*2. wakeup subips*/
        while (this->subips[id]) {
                /*each subip*/
                ret = this->subips[id]->ops->wakeup(this->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: wakeup subip%d-%s failed! %s, %s, %d\n",
                                        id, this->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_wakeup;
                }
                /*next subip*/
                id++;
        }

        /*change state machine 3rd*/
        this->status = RUN;

        printf("INFO: %s wakeup!!!!! %s, %s, %d\n",
                        this->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return ret;
}


/**
 * __tick - tick trigger
 *
 */
static int __tick()
{
        int ret = -1;
        int id = 0;

        if (unlikely(!this)) {
                printf("ERR: product absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: %s tick:%llu come!!!!! %s, %s, %d\n",
                        this->name, tick_counter,
                        __FILE__, __func__, __LINE__);

        /*1. trigger this*/
        //FIXME: todo...

        /*have no subip*/
        if (unlikely(!this->subips)) {
                printf("ERR: %s:subips absent! %s, %s, %d\n",
                                this->name, __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*2. trigger subips*/
        while (this->subips[id]) {
                /*each subip*/
                ret = this->subips[id]->ops->tickarrive(this->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: tick subip%d-%s failed! %s, %s, %d\n",
                                        id, this->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_tick;
                }
                /*next subip*/
                id++;
        }

        /*done*/
        printf("INFO: %s tick:%llu done!!!!! %s, %s, %d\n",
                        this->name, tick_counter,
                        __FILE__, __func__, __LINE__);

ret_tick:
        return ret;
}


/**
 * __dump - dump infos
 *
 */
static int __dump()
{
        int ret = -1;
        int id = 0;

        printf("DEBUG: ========== %s: DUMP START !!!!! ==========\n", this->name);

        if (unlikely(!this)) {
                printf("ERR: product absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*1. dump this*/
        //FIXME: todo...

        /*have no subip*/
        if (unlikely(!this->subips)) {
                printf("ERR: %s:subips absent, please check! %s, %s, %d\n",
                                this->name, __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*2. dump subips*/
        while (this->subips[id]) {
                /*each subip*/
                ret = this->subips[id]->ops->dump(this->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: dump subip%d-%s failed! %s, %s, %d\n",
                                        id, this->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_dump;
                }
                /*next subip*/
                id++;
        }

        printf("DEBUG: ========== %s DUMP END !!!!! ==========\n", this->name);

ret_dump:
        return ret;
}


/**
 * ops structure
 *
 */
static const ip_operations this_ops = {
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
 * struct_alloc - alloc elements
 * @params:    init parameters
 *
 */
static int struct_alloc(param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO need on product level!!!

        /*reg list*/
        if (!params->reg_count) { //FIXME: should separate ips reg count
                printf("INFO: have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        this->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!this->reglist)) {
                printf("ERR: alloc reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)this->reglist, 0, (params->reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                this->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!this->reglist[id])) {
                        printf("ERR: alloc reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)this->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        this->name2reg = init_hashtable();
        if (unlikely(!this->name2reg)) {
                printf("ERR: alloc reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        this->addr2reg = init_hashtable();
        if (unlikely(!this->addr2reg)) {
                printf("ERR: alloc reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        /*subips list*/
        this->subips = malloc((params->board_count +
                                params->boardlink_count + 1) * sizeof(ip *));
        if (unlikely(!this->subips)) {
                printf("ERR: alloc subip array failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)this->subips, 0, (params->board_count +
                                params->boardlink_count + 1) * sizeof(ip *));

        for (id = 0; id < (params->board_count +
                                params->boardlink_count); id++) {
                this->subips[id] = malloc(sizeof(ip));
                if (unlikely(!this->subips[id])) {
                        printf("ERR: alloc subip%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)this->subips[id], 0, sizeof(ip));
        }

        /*subips hastable*/
        this->name2subip = init_hashtable();
        if (unlikely(!this->name2subip)) {
                printf("ERR: alloc subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        this->addr2subip = init_hashtable();
        if (unlikely(!this->addr2subip)) {
                printf("ERR: alloc subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * product_init - init with params
 * @father:    pointer to father struct
 * @product:   pointer to product
 * @id:        product id
 * @params:    init parameters
 *
 */
int product_init(ip *father, ip *self, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: Product Init Start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!self) || unlikely(!params)) {
                printf("ERR: product or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*locally*/
        this = self;

        /*alloc*/
        ret = struct_alloc(params);
        if (unlikely(ret)) {
                printf("ERR: alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(this->name, "product%d", id);

        /*id*/
        this->id = id;

        /*state machine*/
        this->status = OFF;

        /*ops*/
        this->ops = &this_ops;

        /*memory*/
        //NO need on product level!!!

        /*reg list*/
        ret = parse_regconfig(this->reglist);
        if (unlikely(ret)) {
                printf("ERR: %s reglist init failed! %s, %s, %d\n",
                                this->name, __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(this->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(this->reglist[sub]->name,
                                (void *)this->reglist[sub],
                                this->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, this->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", this->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)this->reglist[sub], this->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, this->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        this->address = this->reglist;

        /*parent*/
        this->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        for (sub = 0; sub < params->board_count; sub++) {
                /*call subip:board init function*/
                ret = board_init(this, this->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: board%d init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: boardlink 2nd*/
        for (; sub < (params->board_count + params->boardlink_count); sub++) {
                /*call subip:boardlink init function*/
                ret = boardlink_init(this, this->subips[sub], sub, params);
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
                if (unlikely(!strcmp(this->subips[sub]->name, "")))
                        continue;

                /*table name2subip*/
                ret = insert_hashtable(this->subips[sub]->name,
                                (void *)this->subips[sub],
                                this->name2subip);
                if (unlikely(ret)) {
                        printf("ERR: hash %s to name2subip table failed! %s, %s, %d\n",
                                        this->subips[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2subip*/
                sprintf(addr2str, "0x%x", this->subips[sub]->address);
                ret = insert_hashtable(addr2str, (void *)this->subips[sub],
                                this->addr2subip);
                if (unlikely(ret)) {
                        printf("ERR: hash board/boardlink%d:0x%x to \
                                        addr2subip table failed! %s, %s, %d\n",
                                        sub, this->subips[sub]->address,
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
 *
 */
int product_run()
{
        int ret = -1;

        /*begin*/
        if (unlikely(!this)) {
                printf("ERR: product absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_run;
        }

        /*power on*/
        ret = power_on(this); //power start
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
                ret = clock_run(this); //clock start
                if (unlikely(ret)) {
                        printf("ERR: clock run failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_run;
                }
        }

        /*idle*/
        while (IDLE == global_state) {
                ret = power_idle(this); //internal clock wakeup
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
                ret = power_sleep(this); //outer clock wakeup
                if (unlikely(ret)) {
                        printf("ERR: power sleep failed! %s, %s, %d\n",
                                        __FILE__, __func__, __LINE__);
                        goto ret_run;
                }

                if (unlikely(RUN == global_state))
                        goto running;
        }

        /*power off*/
        power_off(this);

ret_run:
        return ret;
}
