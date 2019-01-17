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
 * __on - main control cpu power on
 * @cp:   cp pointer
 *
 */
static void __on(ip *cp)
{
        if (unlikely(!cp)) {
                printf("ERR: cp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*cp level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        cp->status = RUN;

        printf("INFO: cp:%s power on!!!!! %s, %s, %d\n",
                        cp->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * __off - cp power off
 * @cp:    cp pointer
 *
 */
static void __off(ip *cp)
{
        if (unlikely(!cp)) {
                printf("ERR: cp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //No subips

        /*cp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        cp->status = OFF;

        printf("INFO: cp:%s power off!!!!! %s, %s, %d\n",
                        cp->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * __idle - cp idle
 * @cp:   cp pointer
 *
 */
static void __idle(ip *cp)
{
        if (unlikely(!cp)) {
                printf("ERR: cp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //No subips

        /*cp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        cp->status = IDLE;

        printf("INFO: cp:%s idle!!!!! %s, %s, %d\n",
                        cp->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * __sleep - cp sleep
 * @cp:   cp pointer
 *
 */
static void __sleep(ip *cp)
{
        if (unlikely(!cp)) {
                printf("ERR: cp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //No subips

        /*cp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        cp->status = SLEEP;

        printf("INFO: cp:%s sleep!!!!! %s, %s, %d\n",
                        cp->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * __wakeup - cp wakeup
 * @cp:   cp pointer
 *
 */
static void __wakeup(ip *cp)
{
        if (unlikely(!cp)) {
                printf("ERR: cp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*cp level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        cp->status = RUN;

        printf("INFO: cp:%s wakeup!!!!! %s, %s, %d\n",
                        cp->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * __tick - one tick trigger
 * @cp:   self pointer
 *
 */
static void __tick(ip *cp)
{
        if (unlikely(!cp)) {
                printf("ERR: cp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: cp:%s tick:%llu come!!!!! %s, %s, %d\n",
                        cp->name, tick_counter, __FILE__, __func__, __LINE__);

        /*cp level do 1st*/
        //FIXME: todo...

        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        printf("INFO: cp:%s tick:%llu done!!!!! %s, %s, %d\n",
                        cp->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * __dump - cp dump informations
 * @cp:   cp pointer
 *
 */
static void __dump(ip *cp)
{
        printf("DEBUG: ========== cp:%s dump start !!!!! ==========\n",
                        cp->name);

        if (unlikely(!cp)) {
                printf("ERR: cp absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump cp elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        printf("DEBUG: ========== cp:%s dump end !!!!! ==========\n",
                        cp->name);

ret_dump:
        return;
}
/**
 * ops structure
 *
 */
static const ip_operations cp_ops = {
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
        char *config = "./cp.reg";

        if (unlikely(!reglist)) {
                printf("ERR: cp reglist absent! %s, %s, %d\n",
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
 * cp_alloc - alloc cp elements
 * @cp:   pointer to cp
 * @params:    init parameters
 *
 */
static int cp_alloc(ip *cp, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        if (unlikely(!params->reg_count)) { //FIXME: should separate ips reg count
                printf("INFO: cp have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        cp->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!cp->reglist)) {
                printf("ERR: alloc cp reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)cp->reglist, 0, (params->reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                cp->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!cp->reglist[id])) {
                        printf("ERR: alloc cp reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)cp->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        cp->name2reg = init_hashtable();
        if (unlikely(!cp->name2reg)) {
                printf("ERR: alloc cp reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        cp->addr2reg = init_hashtable();
        if (unlikely(!cp->addr2reg)) {
                printf("ERR: alloc cp reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        /*subips list*/
        //No subips

        /*subips hastable*/
        //No subips

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * cp_init - init cp with params
 * @father:    pointer to the cp belongs to
 * @cp:        pointer to cp
 * @id:        cp id
 * @params:    init parameters
 *
 */
int cp_init(ip *father, ip *cp, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: cp init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!cp) || unlikely(!params)) {
                printf("ERR: cp or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = cp_alloc(cp, params);
        if (unlikely(ret)) {
                printf("ERR: cp alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(cp->name, "cp%d", id);

        /*id*/
        cp->id = id;

        /*state machine*/
        cp->status = OFF;

        /*ops*/
        cp->ops = &cp_ops;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        ret = parse_regconfig(cp->reglist);
        if (unlikely(ret)) {
                printf("ERR: cp reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(cp->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(cp->reglist[sub]->name,
                                (void *)cp->reglist[sub],
                                cp->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, cp->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", cp->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)cp->reglist[sub], cp->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, cp->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        cp->address = cp->reglist;

        /*parent*/
        cp->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        printf("INFO: cp init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
