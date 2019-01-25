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
#include <malloc.h>
#include "common.h"
#include "of.h"
#include "logger.h"



/**
 * __on - fifo power on
 * @fifo:  self pointer
 *
 */
static int __on(ip *fifo)
{
        int ret = -1;

        if (unlikely(!fifo)) {
                ERROR("fifo is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- FIFO %s POWER ON GO>>> -\n", fifo->name);

        /*fifo level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        fifo->status = RUN;

        /*end*/
        INFO("- FIFO %s POWER ON DONE -\n", fifo->name);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - fifo power off
 * @fifo:   self pointer
 *
 */
static int __off(ip *fifo)
{
        int ret = -1;

        if (unlikely(!fifo)) {
                ERROR("fifo is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- FIFO %s POWER OFF GO>>> -\n", fifo->name);

        /*power off subips 1st*/
        //NO subips

        /*fifo level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        fifo->status = OFF;

        /*end*/
        INFO("- FIFO %s POWER OFF DONE -\n", fifo->name);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - fifo idle
 * @fifo:    self pointer
 *
 */
static int __idle(ip *fifo)
{
        int ret = -1;

        if (unlikely(!fifo)) {
                ERROR("fifo is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- FIFO %s IDLE GO>>> -\n", fifo->name);

        /*idle subips 1st*/
        //NO subips

        /*fifo level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        fifo->status = IDLE;

        /*end*/
        INFO("- FIFO %s IDLE DONE -\n", fifo->name);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - fifo sleep
 * @fifo:     self pointer
 *
 */
static int __sleep(ip *fifo)
{
        int ret = -1;

        if (unlikely(!fifo)) {
                ERROR("fifo is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- FIFO %s SLEEP GO>>> -\n", fifo->name);

        /*sleep subips 1st*/
        //NO subips

        /*fifo level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        fifo->status = SLEEP;

        /*end*/
        INFO("- FIFO %s SLEEP DONE -\n", fifo->name);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - fifo wakeup
 * @fifo:      self pointer
 *
 */
static int __wakeup(ip *fifo)
{
        int ret = -1;

        if (unlikely(!fifo)) {
                ERROR("fifo is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- FIFO %s WAKEUP GO>>> -\n", fifo->name);

        /*fifo level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        fifo->status = RUN;

        /*end*/
        INFO("- FIFO %s WAKEUP DONE -\n", fifo->name);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @fifo:    self pointer
 *
 */
static int __tick(ip *fifo)
{
        int ret = -1;

        if (unlikely(!fifo)) {
                ERROR("fifo is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- FIFO %s TICK %llu GO>>> -\n",
                        fifo->name, tick_counter);

        /*fifo level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //NO subips

        /*done*/
        INFO("- FIFO %s TICK %llu DONE -\n",
                        fifo->name, tick_counter);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - fifo dump informations
 * @fifo:  self pointer
 *
 */
static int __dump(ip *fifo)
{
        int ret = -1;

        if (unlikely(!fifo)) {
                ERROR("fifo is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP FIFO %s BEGIN ---\n", fifo->name);

        /*dump fifo elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //NO subips

        /*end*/
        DEBUG("--- DUMP FIFO %s END ---\n", fifo->name);

        ret = 0;
ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations fifo_ops = {
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
        char *config = "./fifo.reg";

        if (unlikely(!reglist)) {
                ERROR("reglist is null !!!\n");
                goto ret_config;
        }

        /*begin*/
        if (unlikely(access(config, F_OK))) {
                WARNING("config file {%s} not exist !!! use default config !!!\n",
                                config);
                ret = 0;
                goto ret_config;
        }

        //FIXME: todo...

ret_config:
        return ret;
}


/**
 * fifo_alloc - alloc fifo elements
 * @fifo:       pointer to fifo
 * @params:    init parameters
 *
 */
static int fifo_alloc(ip *fifo, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        fifo->memory = malloc((params->fifo_count + 1) * sizeof(address32_t *));
        if (unlikely(!fifo->memory)) {
                ERROR("alloc memory failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)fifo->memory, 0, (params->fifo_count + 1) * sizeof(address32_t *));

        for (id = 0; id < params->fifo_count; id++) {
                fifo->memory[id] = malloc(params->fifo_size); //ATT: memory[id]++ is 4bytes
                if (unlikely(!fifo->memory[id])) {
                        ERROR("alloc mem%d failed !!!\n", id);
                        goto ret_alloc;
                }
        }

        /*reg list*/
        if (unlikely(!params->fifo_reg_count)) {
                WARNING("have no register !!!\n");
        }

        //Trick: malloc(0)!=NULL
        fifo->reglist = malloc((params->fifo_reg_count + 1) * sizeof(regs *));
        if (unlikely(!fifo->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)fifo->reglist, 0, (params->fifo_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->fifo_reg_count; id++) {
                fifo->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!fifo->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)fifo->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        fifo->name2reg = init_hashtable();
        if (unlikely(!fifo->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        fifo->addr2reg = init_hashtable();
        if (unlikely(!fifo->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
                goto ret_alloc;
        }

        /*subips list*/
        //NO subips

        /*subips hastable*/
        //NO subips

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * fifo_init - init fifo with params
 * @father:   pointer to the fifo belongs to
 * @fifo:     pointer to fifo
 * @id:       fifo id
 * @params:   init parameters
 *
 */
int fifo_init(ip *father, ip *fifo, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char *addr2str = NULL;

        /*begin*/
        INFO("- FIFO fifo%d INIT GO>>> -\n", id);

        if (unlikely(!fifo) || unlikely(!params)) {
                ERROR("fifo is %p, params is %p !!!\n",
                                fifo, params);
                goto ret_init;
        }

        /*alloc*/
        ret = fifo_alloc(fifo, params);
        if (unlikely(ret)) {
                ERROR("fifo alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(fifo->name, "fifo%d", id);

        /*id*/
        fifo->id = id;

        /*state machine*/
        fifo->status = OFF;

        /*ops*/
        fifo->ops = &fifo_ops;

        /*memory*/
        //Nothing to do.

        /*reg list*/
        ret = parse_regconfig(fifo->reglist);
        if (unlikely(ret)) {
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->fifo_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(fifo->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(fifo->reglist[sub]->name,
                                (void *)fifo->reglist[sub],
                                fifo->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        fifo->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(fifo->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)fifo->reglist[sub], fifo->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        fifo->address = fifo->reglist;

        /*parent*/
        fifo->parent = father;

        /*subips*/
        //NO subips

        /*subips: hashtable*/
        //NO subips

        /*end*/
        INFO("- FIFO fifo%d INIT END -\n", id);

ret_init:
        return ret;
}
