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
 * __on - tp power on
 * @tp:   tp pointer
 *
 */
static void __on(ip *tp)
{
        if (unlikely(!tp)) {
                printf("ERR: tp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*tp level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        tp->status = RUN;

        printf("INFO: tp:%s power on!!!!! %s, %s, %d\n",
                        tp->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * __off - tp power off
 * @tp:    tp pointer
 *
 */
static void __off(ip *tp)
{
        if (unlikely(!tp)) {
                printf("ERR: tp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //No subips

        /*tp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        tp->status = OFF;

        printf("INFO: tp:%s power off!!!!! %s, %s, %d\n",
                        tp->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * __idle - tp idle
 * @tp:   tp pointer
 *
 */
static void __idle(ip *tp)
{
        if (unlikely(!tp)) {
                printf("ERR: tp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //No subips

        /*tp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        tp->status = IDLE;

        printf("INFO: tp:%s idle!!!!! %s, %s, %d\n",
                        tp->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * __sleep - tp sleep
 * @tp:   tp pointer
 *
 */
static void __sleep(ip *tp)
{
        if (unlikely(!tp)) {
                printf("ERR: tp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //No subips

        /*tp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        tp->status = SLEEP;

        printf("INFO: tp:%s sleep!!!!! %s, %s, %d\n",
                        tp->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * __wakeup - tp wakeup
 * @tp:   tp pointer
 *
 */
static void __wakeup(ip *tp)
{
        if (unlikely(!tp)) {
                printf("ERR: tp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*tp level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        tp->status = RUN;

        printf("INFO: tp:%s wakeup!!!!! %s, %s, %d\n",
                        tp->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * __tick - one tick trigger
 * @tp:     self pointer
 *
 */
static void __tick(ip *tp)
{
        if (unlikely(!tp)) {
                printf("ERR: tp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: tp:%s tick:%llu come!!!!! %s, %s, %d\n",
                        tp->name, tick_counter, __FILE__, __func__, __LINE__);

        /*tp level do 1st*/
        //FIXME: todo...

        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        printf("INFO: tp:%s tick:%llu done!!!!! %s, %s, %d\n",
                        tp->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * __dump - tp dump informations
 * @tp:   tp pointer
 *
 */
static void __dump(ip *tp)
{
        int id = 0;

        printf("DEBUG: ========== tp:%s dump start !!!!! ==========\n",
                        tp->name);

        if (unlikely(!tp)) {
                printf("ERR: tp absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump tp elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        printf("DEBUG: ========== tp:%s dump end !!!!! ==========\n",
                        tp->name);

ret_dump:
        return;
}


/**
 * ops structure
 *
 */
static const ip_operations tp_ops = {
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
        char *config = "./tp.reg";

        if (unlikely(!reglist)) {
                printf("ERR: tp reglist absent! %s, %s, %d\n",
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
 * tp_alloc - alloc tp elements
 * @tp:       pointer to tp
 * @params:   init parameters
 *
 */
static int tp_alloc(ip *tp, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO need on tp level!!!

        /*reg list*/
        if (!params->reg_count) { //FIXME: should separate ips reg count
                printf("INFO: tp have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        tp->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!tp->reglist)) {
                printf("ERR: alloc tp reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)tp->reglist, 0, (params->reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                tp->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!tp->reglist[id])) {
                        printf("ERR: alloc tp reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)tp->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        tp->name2reg = init_hashtable();
        if (unlikely(!tp->name2reg)) {
                printf("ERR: alloc tp reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        tp->addr2reg = init_hashtable();
        if (unlikely(!tp->addr2reg)) {
                printf("ERR: alloc tp reg hashtable failed! %s, %s, %d\n",
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
 * tp_init - init tp with params
 * @father:   pointer to the tp belongs to
 * @tp:       pointer to tp
 * @id:       tp id
 * @params:   init parameters
 *
 */
int tp_init(ip *father, ip *tp, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: tp init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!tp) || unlikely(!params)) {
                printf("ERR: tp or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = tp_alloc(tp, params);
        if (unlikely(ret)) {
                printf("ERR: tp alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(tp->name, "tp%d", id);

        /*id*/
        tp->id = id;

        /*state machine*/
        tp->status = OFF;

        /*ops*/
        tp->ops = &tp_ops;

        /*memory*/
        //NO need on tp level!!!

        /*reg list*/
        ret = parse_regconfig(tp->reglist);
        if (unlikely(ret)) {
                printf("ERR: tp reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(tp->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(tp->reglist[sub]->name,
                                (void *)tp->reglist[sub],
                                tp->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, tp->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", tp->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)tp->reglist[sub], tp->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, tp->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        tp->address = tp->reglist;

        /*parent*/
        tp->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        printf("INFO: tp init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
