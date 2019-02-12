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
 * __on - main control cpu power on
 * @maincpu:   maincpu pointer
 *
 */
static int __on(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                ERROR("maincpu is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("MAINCPU %s POWER ON\n", maincpu->name);

        /*maincpu level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        maincpu->status = RUN;

        /*end*/
        INFO("MAINCPU %s POWER ON DONE\n", maincpu->name);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - maincpu power off
 * @maincpu:   maincpu pointer
 *
 */
static int __off(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                ERROR("maincpu is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("MAINCPU %s POWER OFF\n", maincpu->name);

        /*power off subips 1st*/
        //No subips

        /*maincpu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        maincpu->status = OFF;

        /*end*/
        INFO("MAINCPU %s POWER OFF DONE\n", maincpu->name);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - maincpu idle
 * @maincpu:   maincpu pointer
 *
 */
static int __idle(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                ERROR("maincpu is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("MAINCPU %s IDLE\n", maincpu->name);

        /*idle subips 1st*/
        //No subips

        /*maincpu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        maincpu->status = IDLE;

        /*end*/
        INFO("MAINCPU %s IDLE DONE\n", maincpu->name);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - maincpu sleep
 * @maincpu:   maincpu pointer
 *
 */
static int __sleep(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                ERROR("maincpu is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("MAINCPU %s SLEEP\n", maincpu->name);

        /*sleep subips 1st*/
        //No subips

        /*maincpu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        maincpu->status = SLEEP;

        /*end*/
        INFO("MAINCPU %s SLEEP DONE\n", maincpu->name);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - maincpu wakeup
 * @maincpu:   maincpu pointer
 *
 */
static int __wakeup(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                ERROR("maincpu is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("MAINCPU %s WAKEUP\n", maincpu->name);

        /*maincpu level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        maincpu->status = RUN;

        /*end*/
        INFO("MAINCPU %s WAKEUP DONE\n", maincpu->name);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @maincpu:   self pointer
 *
 */
static int __tick(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                ERROR("maincpu is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("MAINCPU %s TICK %llu\n",
                        maincpu->name, tick_counter);

        /*maincpu level do 1st*/
        //FIXME: todo...

        /*tick trigger subips 2nd*/
        //No subips

        /*end*/
        INFO("MAINCPU %s TICK %llu DONE\n",
                        maincpu->name, tick_counter);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - maincpu dump informations
 * @maincpu:   maincpu pointer
 *
 */
static int __dump(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                ERROR("maincpu is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP MAINCPU %s BEGIN ---\n", maincpu->name);

        /*dump maincpu elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        /*end*/
        DEBUG("--- DUMP MAINCPU %s END ---\n", maincpu->name);

        ret = 0;
ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations maincpu_ops = {
        .poweron = __on,
        .poweroff = __off,
        .idle = __idle,
        .sleep = __sleep,
        .wakeup = __wakeup,
        .tickarrive = __tick,
        .dump = __dump,
};


/**
 * parse_regconfig - parse regconfig file regconfig.xxx
 * @reglist:   pointer to reglist
 *
 */
static int parse_regconfig(regs **reglist)
{
        int ret = -1;
        char *regconfig = "./configs/regconfig.maincpu";
        char delimit = 0;

        INFO("parse {%s}\n", regconfig);

        if (unlikely(!reglist)) {
                ERROR("reglist is null !!!\n");
                goto ret_config;
        }

        ret = of_regconfig(regconfig, reglist, delimit);
        if (unlikely(ret)) {
                ERROR("parse regconfig file {%s} failed !!!\n", regconfig);
                goto ret_config;
        }

ret_config:
        return ret;
}


/**
 * maincpu_alloc - alloc maincpu elements
 * @maincpu:   pointer to maincpu
 * @params:    init parameters
 *
 */
static int maincpu_alloc(ip *maincpu, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        if (unlikely(!params->maincpu_reg_count)) {
                WARNING("have no regster !!!\n");
        }

        //Trick: malloc(0)!=NULL
        maincpu->reglist = malloc((params->maincpu_reg_count + 1) * sizeof(regs *));
        if (unlikely(!maincpu->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)maincpu->reglist, 0, (params->maincpu_reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->maincpu_reg_count; id++) {
                maincpu->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!maincpu->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)maincpu->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        maincpu->name2reg = init_hashtable();
        if (unlikely(!maincpu->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        maincpu->addr2reg = init_hashtable();
        if (unlikely(!maincpu->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
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
 * maincpu_init - init maincpu with params
 * @father:    pointer to the maincpu belongs to
 * @maincpu:   pointer to maincpu
 * @id:        maincpu id
 * @params:    init parameters
 *
 */
int maincpu_init(ip *father, ip *maincpu, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char *addr2str = NULL;

        /*begin*/
        INFO("MAINCPU%d INIT\n", id);

        if (unlikely(!maincpu) || unlikely(!params)) {
                ERROR("maincpu is %p, params is %p\n",
                                maincpu, params);
                goto ret_init;
        }

        /*alloc*/
        ret = maincpu_alloc(maincpu, params);
        if (unlikely(ret)) {
                ERROR("maincpu alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(maincpu->name, "maincpu%d", id);

        /*id*/
        maincpu->id = id;

        /*state machine*/
        maincpu->status = OFF;

        /*ops*/
        maincpu->ops = &maincpu_ops;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        ret = parse_regconfig(maincpu->reglist);
        if (unlikely(ret)) {
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->maincpu_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(maincpu->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(maincpu->reglist[sub]->name,
                                (void *)maincpu->reglist[sub],
                                maincpu->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        maincpu->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(maincpu->reglist[sub]->address);
                ret = insert_hashtable(addr2str,
                                (void *)maincpu->reglist[sub],
                                maincpu->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        maincpu->address = maincpu->reglist;

        /*parent*/
        maincpu->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        /*end*/
        INFO("MAINCPU%d INIT DONE\n", id);

ret_init:
        return ret;
}
