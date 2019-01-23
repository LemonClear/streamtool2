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
 * __on - boardlink power on
 * @boardlink:   boardlink pointer
 *
 */
static int __on(ip *boardlink)
{
        int ret = -1;

        if (unlikely(!boardlink)) {
                printf("ERR: boardlink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*boardlink level do 1st*/
        //FIXME: Transparent Transmission temporally on this level

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        boardlink->status = RUN;

        printf("INFO: boardlink:%s power on!!!!! %s, %s, %d\n",
                        boardlink->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - boardlink power off
 * @boardlink:   boardlink pointer
 *
 */
static int __off(ip *boardlink)
{
        int ret = -1;

        if (unlikely(!boardlink)) {
                printf("ERR: boardlink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //No subips

        /*boardlink level do 2nd*/
        //FIXME: Transparent Transmission temporally on this level

        /*change state machine 3rd*/
        boardlink->status = OFF;

        printf("INFO: boardlink:%s power off!!!!! %s, %s, %d\n",
                        boardlink->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - boardlink idle
 * @boardlink:   boardlink pointer
 *
 */
static int __idle(ip *boardlink)
{
        int ret = -1;

        if (unlikely(!boardlink)) {
                printf("ERR: boardlink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //No subips

        /*boardlink level do 2nd*/
        //FIXME: Transparent Transmission temporally on this level

        /*change state machine 3rd*/
        boardlink->status = IDLE;

        printf("INFO: boardlink:%s idle!!!!! %s, %s, %d\n",
                        boardlink->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - boardlink sleep
 * @boardlink:   boardlink pointer
 *
 */
static int __sleep(ip *boardlink)
{
        int ret = -1;

        if (unlikely(!boardlink)) {
                printf("ERR: boardlink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //No subips

        /*boardlink level do 2nd*/
        //FIXME: Transparent Transmission temporally on this level

        /*change state machine 3rd*/
        boardlink->status = SLEEP;

        printf("INFO: boardlink:%s sleep!!!!! %s, %s, %d\n",
                        boardlink->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - boardlink wakeup
 * @boardlink:   boardlink pointer
 *
 */
static int __wakeup(ip *boardlink)
{
        int ret = -1;

        if (unlikely(!boardlink)) {
                printf("ERR: boardlink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*boardlink level do 1st*/
        //FIXME: Transparent Transmission temporally on this level

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        boardlink->status = RUN;

        printf("INFO: boardlink:%s wakeup!!!!! %s, %s, %d\n",
                        boardlink->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @boardlink:   self pointer
 *
 */
static int __tick(ip *boardlink)
{
        int ret = -1;

        if (unlikely(!boardlink)) {
                printf("ERR: boardlink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: boardlink:%s tick:%llu come!!!!! %s, %s, %d\n",
                        boardlink->name, tick_counter, __FILE__, __func__, __LINE__);

        /*boardlink level do 1st*/
        //FIXME: Transparent Transmission temporally on this level


        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        printf("INFO: boardlink:%s tick:%llu done!!!!! %s, %s, %d\n",
                        boardlink->name, tick_counter, __FILE__, __func__, __LINE__);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - boardlink dump informations
 * @boardlink:   boardlink pointer
 *
 */
static int __dump(ip *boardlink)
{
        int ret = -1;

        printf("DEBUG: ========== boardlink:%s dump start !!!!! ==========\n",
                        boardlink->name);

        if (unlikely(!boardlink)) {
                printf("ERR: boardlink absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump boardlink elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        printf("DEBUG: ========== boardlink:%s dump end !!!!! ==========\n",
                        boardlink->name);

        ret = 0;
ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations boardlink_ops = {
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
        char *config = "./boardlink.reg";

        if (unlikely(!reglist)) {
                printf("ERR: boardlink reglist absent! %s, %s, %d\n",
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
 * boardlink_alloc - alloc boardlink elements
 * @boardlink: pointer to boardlink
 * @params:    init parameters
 *
 */
static int boardlink_alloc(ip *boardlink, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //FIXME: DO NOTHING!!!
        //NO NEED on boardlink level!!!

        /*reg list*/
        if (unlikely(!params->boardlink_reg_count)) {
                printf("INFO: boardlink have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        boardlink->reglist = malloc((params->boardlink_reg_count + 1) * sizeof(regs *));
        if (unlikely(!boardlink->reglist)) {
                printf("ERR: alloc boardlink reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)boardlink->reglist, 0, (params->boardlink_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->boardlink_reg_count; id++) {
                boardlink->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!boardlink->reglist[id])) {
                        printf("ERR: alloc boardlink reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)boardlink->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        boardlink->name2reg = init_hashtable();
        if (unlikely(!boardlink->name2reg)) {
                printf("ERR: alloc boardlink reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        boardlink->addr2reg = init_hashtable();
        if (unlikely(!boardlink->addr2reg)) {
                printf("ERR: alloc boardlink reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        /*subips list*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*subips hastable*/
        //FIXME: DO NOTHING!!!
        //No subips

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * boardlink_init - init boardlink with params
 * @father:    pointer to boardlink belongs to
 * @boardlink: pointer to boardlink
 * @id:        boardlink id
 * @params:    init parameters
 *
 */
int boardlink_init(ip *father, ip *boardlink, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: boardlink init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!boardlink) || unlikely(!params)) {
                printf("ERR: ip or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = boardlink_alloc(boardlink, params);
        if (unlikely(ret)) {
                printf("ERR: boardlink alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(boardlink->name, "boardlink%d", id);

        /*id*/
        boardlink->id = id;

        /*state machine*/
        boardlink->status = OFF;

        /*ops*/
        boardlink->ops = &boardlink_ops;

        /*memory*/
        //FIXME: DO NOTHING!!!
        //NO NEED on boardlink level!!!

        /*reg list*/
        ret = parse_regconfig(boardlink->reglist);
        if (unlikely(ret)) {
                printf("ERR: boardlink reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->boardlink_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(boardlink->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(boardlink->reglist[sub]->name,
                                (void *)boardlink->reglist[sub],
                                boardlink->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, boardlink->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", boardlink->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)boardlink->reglist[sub], boardlink->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, boardlink->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        boardlink->address = boardlink->reglist;

        /*parent*/
        boardlink->parent = father;

        /*connected*/
        //No connected

        /*subips*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*subips: hashtable*/
        //FIXME: DO NOTHING!!!
        //No subips

        printf("INFO: boardlink init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
