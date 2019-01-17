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
 * __on - chiplink power on
 * @chiplink:  chiplink pointer
 *
 */
static void __on(ip *chiplink)
{
        if (unlikely(!chiplink)) {
                printf("ERR: chiplink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*chiplink level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*change state machine 3rd*/
        chiplink->status = RUN;

        printf("INFO: chiplink:%s power on!!!!! %s, %s, %d\n",
                        chiplink->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * __off - chiplink power off
 * @chiplink:   chiplink pointer
 *
 */
static void __off(ip *chiplink)
{
        if (unlikely(!chiplink)) {
                printf("ERR: chiplink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*chiplink level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        chiplink->status = OFF;

        printf("INFO: chiplink:%s power off!!!!! %s, %s, %d\n",
                        chiplink->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * __idle - chiplink idle
 * @chiplink:   chiplink pointer
 *
 */
static void __idle(ip *chiplink)
{
        if (unlikely(!chiplink)) {
                printf("ERR: chiplink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*chiplink level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        chiplink->status = IDLE;

        printf("INFO: chiplink:%s idle!!!!! %s, %s, %d\n",
                        chiplink->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * sleep - chiplink sleep
 * @chiplink:   chiplink pointer
 *
 */
static void __sleep(ip *chiplink)
{
        if (unlikely(!chiplink)) {
                printf("ERR: chiplink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*chiplink level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        chiplink->status = SLEEP;

        printf("INFO: chiplink:%s sleep!!!!! %s, %s, %d\n",
                        chiplink->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * __wakeup - chiplink wakeup
 * @chiplink:   chiplink pointer
 *
 */
static void __wakeup(ip *chiplink)
{
        if (unlikely(!chiplink)) {
                printf("ERR: chiplink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*chiplink level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*change state machine 3rd*/
        chiplink->status = RUN;

        printf("INFO: chiplink:%s wakeup!!!!! %s, %s, %d\n",
                        chiplink->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * __tick - one tick trigger
 * @chiplink:   self pointer
 *
 */
static void __tick(ip *chiplink)
{
        if (unlikely(!chiplink)) {
                printf("ERR: chiplink absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: chiplink:%s tick:%llu come!!!!! %s, %s, %d\n",
                        chiplink->name, tick_counter, __FILE__, __func__, __LINE__);

        /*chiplink level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*done*/
        printf("INFO: chiplink:%s tick:%llu done!!!!! %s, %s, %d\n",
                        chiplink->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * __dump - chiplink dump informations
 * @chiplink:  chiplink pointer
 *
 */
static void __dump(ip *chiplink)
{
        printf("DEBUG: ========== chiplink:%s dump start !!!!! ==========\n",
                        chiplink->name);

        if (unlikely(!chiplink)) {
                printf("ERR: chiplink absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump chiplink elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        printf("DEBUG: ========== chiplink:%s dump end !!!!! ==========\n",
                        chiplink->name);

ret_dump:
        return;
}
/**
 * ops structure
 *
 */
static const ip_operations chiplink_ops = {
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
        char *config = "./chiplink.reg";

        if (unlikely(!reglist)) {
                printf("ERR: chiplink reglist absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_config;
        }

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
 * chiplink_alloc - alloc chiplink elements
 * @chiplink:   pointer to chiplink
 * @params:    init parameters
 *
 */
static int chiplink_alloc(ip *chiplink, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //FIXME: DO NOTHING!!!
        //NO NEED on chiplink level!!!

        /*reg list*/
        if (unlikely(!params->reg_count)) { //FIXME: should separate ips reg count
                printf("INFO: chiplink have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL, if have no reg,
        //the chiplink->reglist value can also mark as this ip's address
        chiplink->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!chiplink->reglist)) {
                printf("ERR: alloc chiplink reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)chiplink->reglist, 0, (params->reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                chiplink->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!chiplink->reglist[id])) {
                        printf("ERR: alloc chiplink reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)chiplink->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        chiplink->name2reg = init_hashtable();
        if (unlikely(!chiplink->name2reg)) {
                printf("ERR: alloc chiplink reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        chiplink->addr2reg = init_hashtable();
        if (unlikely(!chiplink->addr2reg)) {
                printf("ERR: alloc chiplink reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        /*subips list*/
        //FIXME: DO NOTHING!!!
        //NO subips

        /*subips hastable*/
        //FIXME: DO NOTHING!!!
        //No subips

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * chiplink_init - init chiplink with params
 * @father:    pointer to the chiplink belongs to
 * @chiplink:  pointer to chiplink
 * @id:        chiplink id
 * @params:    init parameters
 *
 */
int chiplink_init(ip *father, ip *chiplink, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: chiplink init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!chiplink) || unlikely(!params)) {
                printf("ERR: chiplink or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = chiplink_alloc(chiplink, params);
        if (unlikely(ret)) {
                printf("ERR: chiplink alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(chiplink->name, "chiplink%d", id);

        /*id*/
        chiplink->id = id;

        /*state machine*/
        chiplink->status = OFF;

        /*ops*/
        chiplink->ops = &chiplink_ops;

        /*memory*/
        //NO NEED on chiplink level!!!

        /*reg list*/
        ret = parse_regconfig(chiplink->reglist);
        if (unlikely(ret)) {
                printf("ERR: chiplink reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(chiplink->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(chiplink->reglist[sub]->name,
                                (void *)chiplink->reglist[sub],
                                chiplink->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, chiplink->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", chiplink->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)chiplink->reglist[sub], chiplink->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, chiplink->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        chiplink->address = chiplink->reglist;

        /*parent*/
        chiplink->parent = father;

        /*connected*/
        //No connected

        /*subips: chiplink 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*subips: hashtable*/
        //FIXME: DO NOTHING!!!
        //No subips

        printf("INFO: chiplink init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
