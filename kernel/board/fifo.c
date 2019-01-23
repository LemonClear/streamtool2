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



/**
 * __on - fifo power on
 * @fifo:  self pointer
 *
 */
static int __on(ip *fifo)
{
        int ret = -1;

        if (unlikely(!fifo)) {
                printf("ERR: fifo absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*fifo level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        fifo->status = RUN;

        printf("INFO: fifo:%s power on!!!!! %s, %s, %d\n",
                        fifo->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: fifo absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //NO subips

        /*fifo level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        fifo->status = OFF;

        printf("INFO: fifo:%s power off!!!!! %s, %s, %d\n",
                        fifo->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: fifo absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //NO subips

        /*fifo level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        fifo->status = IDLE;

        printf("INFO: fifo:%s idle!!!!! %s, %s, %d\n",
                        fifo->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: fifo absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //NO subips

        /*fifo level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        fifo->status = SLEEP;

        printf("INFO: fifo:%s sleep!!!!! %s, %s, %d\n",
                        fifo->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: fifo absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*fifo level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        fifo->status = RUN;

        printf("INFO: fifo:%s wakeup!!!!! %s, %s, %d\n",
                        fifo->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: fifo absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: fifo:%s tick:%llu come!!!!! %s, %s, %d\n",
                        fifo->name, tick_counter, __FILE__, __func__, __LINE__);

        /*fifo level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //NO subips

        /*done*/
        printf("INFO: fifo:%s tick:%llu done!!!!! %s, %s, %d\n",
                        fifo->name, tick_counter, __FILE__, __func__, __LINE__);

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

        printf("DEBUG: ========== fifo:%s dump start !!!!! ==========\n",
                        fifo->name);

        if (unlikely(!fifo)) {
                printf("ERR: fifo absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump fifo elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //NO subips

        printf("DEBUG: ========== fifo:%s dump end !!!!! ==========\n",
                        fifo->name);

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
                printf("ERR: fifo reglist absent! %s, %s, %d\n",
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
                printf("ERR: alloc fifo memory failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)fifo->memory, 0, (params->fifo_count + 1) * sizeof(address32_t *));

        for (id = 0; id < params->fifo_count; id++) {
                fifo->memory[id] = malloc(params->fifo_size); //ATT: memory[id]++ is 4bytes
                if (unlikely(!fifo->memory[id])) {
                        printf("ERR: alloc fifo mem%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
        }

        /*reg list*/
        if (unlikely(!params->fifo_reg_count)) {
                printf("INFO: fifo have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        fifo->reglist = malloc((params->fifo_reg_count + 1) * sizeof(regs *));
        if (unlikely(!fifo->reglist)) {
                printf("ERR: alloc fifo reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)fifo->reglist, 0, (params->fifo_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->fifo_reg_count; id++) {
                fifo->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!fifo->reglist[id])) {
                        printf("ERR: alloc fifo reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)fifo->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        fifo->name2reg = init_hashtable();
        if (unlikely(!fifo->name2reg)) {
                printf("ERR: alloc fifo reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        fifo->addr2reg = init_hashtable();
        if (unlikely(!fifo->addr2reg)) {
                printf("ERR: alloc fifo reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: fifo init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!fifo) || unlikely(!params)) {
                printf("ERR: fifo or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = fifo_alloc(fifo, params);
        if (unlikely(ret)) {
                printf("ERR: fifo alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
                printf("ERR: fifo reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, fifo->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", fifo->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)fifo->reglist[sub], fifo->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, fifo->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
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

        printf("INFO: fifo init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
