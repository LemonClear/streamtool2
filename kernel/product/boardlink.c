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
 * __on - boardlink power on
 * @boardlink:   boardlink pointer
 *
 */
static int __on(ip *boardlink)
{
        int ret = -1;

        if (unlikely(!boardlink)) {
                ERROR("boardlink is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- BOARDLINK %s POWER ON GO... -\n", boardlink->name);

        /*boardlink level do 1st*/
        //FIXME: Transparent Transmission temporally on this level

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        boardlink->status = RUN;

        /*end*/
        INFO("- BOARDLINK %s POWER ON DONE -\n", boardlink->name);

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
                ERROR("boardlink is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- BOARDLINK %s POWER OFF GO... -\n", boardlink->name);

        /*power off subips 1st*/
        //No subips

        /*boardlink level do 2nd*/
        //FIXME: Transparent Transmission temporally on this level

        /*change state machine 3rd*/
        boardlink->status = OFF;

        /*end*/
        INFO("- BOARDLINK %s POWER OFF DONE -\n", boardlink->name);

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
                ERROR("boardlink is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- BOARDLINK %s IDLE GO... -\n", boardlink->name);

        /*idle subips 1st*/
        //No subips

        /*boardlink level do 2nd*/
        //FIXME: Transparent Transmission temporally on this level

        /*change state machine 3rd*/
        boardlink->status = IDLE;

        /*end*/
        INFO("- BOARDLINK %s IDLE DONE -\n", boardlink->name);

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
                ERROR("boardlink is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- BOARDLINK %s SLEEP GO... -\n", boardlink->name);

        /*sleep subips 1st*/
        //No subips

        /*boardlink level do 2nd*/
        //FIXME: Transparent Transmission temporally on this level

        /*change state machine 3rd*/
        boardlink->status = SLEEP;

        /*end*/
        INFO("- BOARDLINK %s SLEEP DONE -\n", boardlink->name);

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
                ERROR("boardlink is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- BOARDLINK %s WAKEUP GO... -\n", boardlink->name);

        /*boardlink level do 1st*/
        //FIXME: Transparent Transmission temporally on this level

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        boardlink->status = RUN;

        /*begin*/
        INFO("- BOARDLINK %s WAKEUP DONE -\n", boardlink->name);

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
                ERROR("boardlink is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- BOARDLINK %s TICK %llu GO... -\n",
                        boardlink->name, tick_counter);

        /*boardlink level do 1st*/
        //FIXME: Transparent Transmission temporally on this level


        /*tick trigger subips 2nd*/
        //No subips

        /*end*/
        INFO("- BOARDLINK %s TICK %llu DONE -\n",
                        boardlink->name, tick_counter);

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

        /*begin*/
        DEBUG("--- DUMP BOARDLINK %s BEGIN ---\n", boardlink->name);

        if (unlikely(!boardlink)) {
                ERROR("boardlink is null !!!\n");
                goto ret_dump;
        }

        /*dump boardlink elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        /*end*/
        DEBUG("--- DUMP BOARDLINK %s END ---\n", boardlink->name);

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
                ERROR("reglist is null !!!\n");
                goto ret_config;
        }

        /*begin*/
        if (unlikely(access(config, F_OK))) {
                WARNING("config file %s not exist !!! use default config !!!\n",
                                config);
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
                WARNING("have no register !!!\n");
        }

        //Trick: malloc(0)!=NULL
        boardlink->reglist = malloc((params->boardlink_reg_count + 1) * sizeof(regs *));
        if (unlikely(!boardlink->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)boardlink->reglist, 0, (params->boardlink_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->boardlink_reg_count; id++) {
                boardlink->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!boardlink->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)boardlink->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        boardlink->name2reg = init_hashtable();
        if (unlikely(!boardlink->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        boardlink->addr2reg = init_hashtable();
        if (unlikely(!boardlink->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
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
        INFO("- BOARDLINK boardlink%d INIT GO... -\n", id);

        if (unlikely(!boardlink) || unlikely(!params)) {
                ERROR("boardlink is %p, params is %p !!!\n", boardlink, params);
                goto ret_init;
        }

        /*alloc*/
        ret = boardlink_alloc(boardlink, params);
        if (unlikely(ret)) {
                ERROR("boardlink alloc elements failed !!!\n");
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
                ERROR("boardlink reglist init failed !!!\n");
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
                        ERROR("hash %s to name2reg failed !!!\n",
                                        boardlink->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", boardlink->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)boardlink->reglist[sub], boardlink->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
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

        /*end*/
        INFO("- BOARDLINK boardlink%d INIT DONE -\n", id);

ret_init:
        return ret;
}
