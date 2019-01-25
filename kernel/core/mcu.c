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
 * @mcu:   mcu pointer
 *
 */
static int __on(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                ERROR("mcu is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- MCU %s POWER ON GO... -\n", mcu->name);

        /*mcu level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        mcu->status = RUN;

        /*end*/
        INFO("- MCU %s POWER ON DONE -\n", mcu->name);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - mcu power off
 * @mcu:    mcu pointer
 *
 */
static int __off(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                ERROR("mcu is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- MCU %s POWER OFF GO... -\n", mcu->name);

        /*power off subips 1st*/
        //No subips

        /*mcu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        mcu->status = OFF;

        /*end*/
        INFO("- MCU %s POWER OFF DONE -\n", mcu->name);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - mcu idle
 * @mcu:   mcu pointer
 *
 */
static int __idle(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                ERROR("mcu is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- MCU %s IDLE GO... -\n", mcu->name);

        /*idle subips 1st*/
        //No subips

        /*mcu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        mcu->status = IDLE;

        /*end*/
        INFO("- MCU %s IDLE DONE -\n", mcu->name);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - mcu sleep
 * @mcu:   mcu pointer
 *
 */
static int __sleep(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                ERROR("mcu is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- MCU %s SLEEP GO... -\n", mcu->name);

        /*sleep subips 1st*/
        //No subips

        /*mcu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        mcu->status = SLEEP;

        /*end*/
        INFO("- MCU %s SLEEP DONE -\n", mcu->name);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - mcu wakeup
 * @mcu:   mcu pointer
 *
 */
static int __wakeup(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                ERROR("mcu is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- MCU %s WAKEUP GO... -\n", mcu->name);

        /*mcu level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        mcu->status = RUN;

        /*end*/
        INFO("- MCU %s WAKEUP DONE -\n", mcu->name);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @mcu:   self pointer
 *
 */
static int __tick(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                ERROR("mcu is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- MCU %s TICK %llu GO >>> -\n",
                        mcu->name, tick_counter);

        /*mcu level do 1st*/
        //FIXME: todo...

        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        INFO("- MCU %s TICK %llu DONE -\n",
                        mcu->name, tick_counter);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - mcu dump informations
 * @mcu:   mcu pointer
 *
 */
static int __dump(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                ERROR("mcu is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP MCU %s BEGIN ---\n", mcu->name);

        /*dump mcu elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        /*end*/
        DEBUG("--- DUMP MCU %s END ---\n", mcu->name);

        ret = 0;
ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations mcu_ops = {
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
        char *config = "./mcu.reg";

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
 * mcu_alloc - alloc mcu elements
 * @mcu:   pointer to mcu
 * @params:    init parameters
 *
 */
static int mcu_alloc(ip *mcu, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        if (unlikely(!params->mcu_reg_count)) {
                WARNING("have no regster !!!\n");
        }

        //Trick: malloc(0)!=NULL
        mcu->reglist = malloc((params->mcu_reg_count + 1) * sizeof(regs *));
        if (unlikely(!mcu->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)mcu->reglist, 0, (params->mcu_reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->mcu_reg_count; id++) {
                mcu->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!mcu->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)mcu->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        mcu->name2reg = init_hashtable();
        if (unlikely(!mcu->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        mcu->addr2reg = init_hashtable();
        if (unlikely(!mcu->addr2reg)) {
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
 * mcu_init - init mcu with params
 * @father:    pointer to the mcu belongs to
 * @mcu:       pointer to mcu
 * @id:        mcu id
 * @params:    init parameters
 *
 */
int mcu_init(ip *father, ip *mcu, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char *addr2str = NULL;

        /*begin*/
        INFO("- MCU mcu%d INIT GO >>> -\n", id);

        if (unlikely(!mcu) || unlikely(!params)) {
                ERROR("mcu is %p, params is %p\n",
                                mcu, params);
                goto ret_init;
        }

        /*alloc*/
        ret = mcu_alloc(mcu, params);
        if (unlikely(ret)) {
                ERROR("mcu alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(mcu->name, "mcu%d", id);

        /*id*/
        mcu->id = id;

        /*state machine*/
        mcu->status = OFF;

        /*ops*/
        mcu->ops = &mcu_ops;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        ret = parse_regconfig(mcu->reglist);
        if (unlikely(ret)) {
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->mcu_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(mcu->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(mcu->reglist[sub]->name,
                                (void *)mcu->reglist[sub],
                                mcu->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        mcu->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(mcu->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)mcu->reglist[sub], mcu->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        mcu->address = mcu->reglist;

        /*parent*/
        mcu->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        /*end*/
        INFO("- MCU mcu%d INIT DONE -\n", id);

ret_init:
        return ret;
}
