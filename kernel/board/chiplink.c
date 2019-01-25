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
 * __on - chiplink power on
 * @chiplink:  chiplink pointer
 *
 */
static int __on(ip *chiplink)
{
        int ret = -1;

        if (unlikely(!chiplink)) {
                ERROR("chiplink is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- CHIPLINK %s POWER ON GO... -\n", chiplink->name);

        /*chiplink level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*change state machine 3rd*/
        chiplink->status = RUN;

        /*end*/
        INFO("- CHIPLINK %s POWER ON DONE -\n", chiplink->name);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - chiplink power off
 * @chiplink:   chiplink pointer
 *
 */
static int __off(ip *chiplink)
{
        int ret = -1;

        if (unlikely(!chiplink)) {
                ERROR("chiplink is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- CHIPLINK %s POWER OFF GO... -\n", chiplink->name);

        /*power off subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*chiplink level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        chiplink->status = OFF;

        /*end*/
        INFO("- CHIPLINK %s POWER OFF DONE -\n", chiplink->name);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - chiplink idle
 * @chiplink:   chiplink pointer
 *
 */
static int __idle(ip *chiplink)
{
        int ret = -1;

        if (unlikely(!chiplink)) {
                ERROR("chiplink is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- CHIPLINK %s IDLE GO... -\n", chiplink->name);

        /*idle subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*chiplink level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        chiplink->status = IDLE;

        /*end*/
        INFO("- CHIPLINK %s IDLE DONE -\n", chiplink->name);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * sleep - chiplink sleep
 * @chiplink:   chiplink pointer
 *
 */
static int __sleep(ip *chiplink)
{
        int ret = -1;

        if (unlikely(!chiplink)) {
                ERROR("chiplink is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- CHIPLINK %s SLEEP GO... -\n", chiplink->name);

        /*sleep subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*chiplink level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        chiplink->status = SLEEP;

        /*end*/
        INFO("- CHIPLINK %s SLEEP DONE -\n", chiplink->name);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - chiplink wakeup
 * @chiplink:   chiplink pointer
 *
 */
static int __wakeup(ip *chiplink)
{
        int ret = -1;

        if (unlikely(!chiplink)) {
                ERROR("chiplink is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- CHIPLINK %s WAKEUP GO... -\n", chiplink->name);

        /*chiplink level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*change state machine 3rd*/
        chiplink->status = RUN;

        /*end*/
        INFO("- CHIPLINK %s WAKEUP DONE -\n", chiplink->name);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @chiplink:   self pointer
 *
 */
static int __tick(ip *chiplink)
{
        int ret = -1;

        if (unlikely(!chiplink)) {
                ERROR("chiplink is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- CHIPLINK %s TICK %llu GO... -\n",
                        chiplink->name, tick_counter);

        /*chiplink level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*done*/
        INFO("- CHIPLINK %s TICK %llu DONE -\n",
                        chiplink->name, tick_counter);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - chiplink dump informations
 * @chiplink:  chiplink pointer
 *
 */
static int __dump(ip *chiplink)
{
        int ret = -1;

        if (unlikely(!chiplink)) {
                ERROR("chiplink is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP CHIPLINK %s BEGIN ---\n", chiplink->name);

        /*dump chiplink elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*end*/
        DEBUG("--- DUMP CHIPLINK %s END ---\n", chiplink->name);

        ret = 0;
ret_dump:
        return ret;
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
                ERROR("reglist is null !!!\n");
                goto ret_config;
        }

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
        if (unlikely(!params->chiplink_reg_count)) {
                WARNING("have no register !!!\n");
        }

        //Trick: malloc(0)!=NULL, if have no reg,
        //the chiplink->reglist value can also mark as this ip's address
        chiplink->reglist = malloc((params->chiplink_reg_count + 1) * sizeof(regs *));
        if (unlikely(!chiplink->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)chiplink->reglist, 0, (params->chiplink_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->chiplink_reg_count; id++) {
                chiplink->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!chiplink->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)chiplink->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        chiplink->name2reg = init_hashtable();
        if (unlikely(!chiplink->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        chiplink->addr2reg = init_hashtable();
        if (unlikely(!chiplink->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
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
        char *addr2str = NULL;

        /*begin*/
        INFO("- CHIPLINK chiplink%d INIT GO... -\n", id);

        if (unlikely(!chiplink) || unlikely(!params)) {
                ERROR("chiplink is %p, params is %p !!!\n",
                                chiplink, params);
                goto ret_init;
        }

        /*alloc*/
        ret = chiplink_alloc(chiplink, params);
        if (unlikely(ret)) {
                ERROR("chiplink alloc elements failed !!!\n");
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
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->chiplink_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(chiplink->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(chiplink->reglist[sub]->name,
                                (void *)chiplink->reglist[sub],
                                chiplink->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        chiplink->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(chiplink->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)chiplink->reglist[sub], chiplink->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
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

        /*end*/
        INFO("- CHIPLINK chiplink%d INIT DONE -\n", id);

ret_init:
        return ret;
}
