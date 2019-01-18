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
 * __on - np power on
 * @np:   np pointer
 *
 */
static int __on(ip *np)
{
        int ret = -1;

        if (unlikely(!np)) {
                printf("ERR: np absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*np level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        np->status = RUN;

        printf("INFO: np:%s power on!!!!! %s, %s, %d\n",
                        np->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - np power off
 * @np:    np pointer
 *
 */
static int __off(ip *np)
{
        int ret = -1;

        if (unlikely(!np)) {
                printf("ERR: np absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //NO subips

        /*np level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        np->status = OFF;

        printf("INFO: np:%s power off!!!!! %s, %s, %d\n",
                        np->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - np idle
 * @np:   np pointer
 *
 */
static int __idle(ip *np)
{
        int ret = -1;

        if (unlikely(!np)) {
                printf("ERR: np absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //NO subips

        /*np level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        np->status = IDLE;

        printf("INFO: np:%s idle!!!!! %s, %s, %d\n",
                        np->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - np sleep
 * @np:   np pointer
 *
 */
static int __sleep(ip *np)
{
        int ret = -1;

        if (unlikely(!np)) {
                printf("ERR: np absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //NO subips

        /*np level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        np->status = SLEEP;

        printf("INFO: np:%s sleep!!!!! %s, %s, %d\n",
                        np->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - np wakeup
 * @np:   np pointer
 *
 */
static int __wakeup(ip *np)
{
        int ret = -1;
        int id = -1;

        if (unlikely(!np)) {
                printf("ERR: np absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*np level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        np->status = RUN;

        printf("INFO: np:%s wakeup!!!!! %s, %s, %d\n",
                        np->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @np:   self pointer
 *
 */
static int __tick(ip *np)
{
        int ret = -1;

        if (unlikely(!np)) {
                printf("ERR: np absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: np:%s tick:%llu come!!!!! %s, %s, %d\n",
                        np->name, tick_counter, __FILE__, __func__, __LINE__);

        /*np level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //NO subips

        /*done*/
        printf("INFO: np:%s tick:%llu done!!!!! %s, %s, %d\n",
                        np->name, tick_counter, __FILE__, __func__, __LINE__);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - np dump informations
 * @np:   np pointer
 *
 */
static int __dump(ip *np)
{
        int ret = -1;
        int id = -1;

        printf("DEBUG: ========== np:%s dump start !!!!! ==========\n",
                        np->name);

        if (unlikely(!np)) {
                printf("ERR: np absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump np elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //NO subips

        printf("DEBUG: ========== np:%s dump end !!!!! ==========\n",
                        np->name);

        ret = 0;
ret_dump:
        return ret;
}


/**
 * ops structure
 *
 */
static const ip_operations np_ops = {
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
        char *config = "./np.reg";

        if (unlikely(!reglist)) {
                printf("ERR: np reglist absent! %s, %s, %d\n",
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
 * np_alloc - alloc np elements
 * @np:   pointer to np
 * @params:    init parameters
 *
 */
static int np_alloc(ip *np, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO need on np level!!!

        /*reg list*/
        if (unlikely(!params->reg_count)) { //FIXME: should separate ips reg count
                printf("INFO: np have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        np->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!np->reglist)) {
                printf("ERR: alloc np reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)np->reglist, 0, (params->reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                np->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!np->reglist[id])) {
                        printf("ERR: alloc np reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)np->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        np->name2reg = init_hashtable();
        if (unlikely(!np->name2reg)) {
                printf("ERR: alloc np reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        np->addr2reg = init_hashtable();
        if (unlikely(!np->addr2reg)) {
                printf("ERR: alloc np reg hashtable failed! %s, %s, %d\n",
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
 * np_init - init np with params
 * @father:    pointer to the np belongs to
 * @np:        pointer to np
 * @id:        np id
 * @params:    init parameters
 *
 */
int np_init(ip *father, ip *np, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: np init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!np) || unlikely(!params)) {
                printf("ERR: np or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = np_alloc(np, params);
        if (unlikely(ret)) {
                printf("ERR: np alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(np->name, "np%d", id);

        /*id*/
        np->id = id;

        /*state machine*/
        np->status = OFF;

        /*ops*/
        np->ops = &np_ops;

        /*memory*/
        //NO need on np level!!!

        /*reg list*/
        ret = parse_regconfig(np->reglist);
        if (unlikely(ret)) {
                printf("ERR: np reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(np->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(np->reglist[sub]->name,
                                (void *)np->reglist[sub],
                                np->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, np->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", np->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)np->reglist[sub], np->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, np->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        np->address = np->reglist;

        /*parent*/
        np->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        printf("INFO: np init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
