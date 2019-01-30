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
 * __on - ncp power on
 * @ncp:   ncp pointer
 *
 */
static int __on(ip *ncp)
{
        int ret = -1;

        if (unlikely(!ncp)) {
                ERROR("ncp is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("NCP %s POWER ON\n", ncp->name);

        /*ncp level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ncp->status = RUN;

        /*end*/
        INFO("NCP %s POWER ON DONE\n", ncp->name);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - ncp power off
 * @ncp:    ncp pointer
 *
 */
static int __off(ip *ncp)
{
        int ret = -1;

        if (unlikely(!ncp)) {
                ERROR("ncp is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("NCP %s POWER OFF\n", ncp->name);

        /*power off subips 1st*/
        //NO subips

        /*ncp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ncp->status = OFF;

        /*end*/
        INFO("NCP %s POWER OFF DONE\n", ncp->name);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - ncp idle
 * @ncp:   ncp pointer
 *
 */
static int __idle(ip *ncp)
{
        int ret = -1;

        if (unlikely(!ncp)) {
                ERROR("ncp is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("NCP %s IDLE\n", ncp->name);

        /*idle subips 1st*/
        //NO subips

        /*ncp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ncp->status = IDLE;

        /*end*/
        INFO("NCP %s IDLE DONE\n", ncp->name);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - ncp sleep
 * @ncp:   ncp pointer
 *
 */
static int __sleep(ip *ncp)
{
        int ret = -1;

        if (unlikely(!ncp)) {
                ERROR("ncp is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("NCP %s SLEEP\n", ncp->name);

        /*sleep subips 1st*/
        //NO subips

        /*ncp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ncp->status = SLEEP;

        /*end*/
        INFO("NCP %s SLEEP DONE\n", ncp->name);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - ncp wakeup
 * @ncp:   ncp pointer
 *
 */
static int __wakeup(ip *ncp)
{
        int ret = -1;
        int id = -1;

        if (unlikely(!ncp)) {
                ERROR("ncp is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("NCP %s WAKEUP\n", ncp->name);

        /*ncp level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ncp->status = RUN;

        /*end*/
        INFO("NCP %s WAKEUP DONE\n", ncp->name);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @ncp:   self pointer
 *
 */
static int __tick(ip *ncp)
{
        int ret = -1;

        if (unlikely(!ncp)) {
                ERROR("ncp is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("NCP %s TICK %llu\n", ncp->name, tick_counter);

        /*ncp level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //NO subips

        /*done*/
        INFO("NCP %s TICK %llu DONE\n", ncp->name, tick_counter);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - ncp dump informations
 * @ncp:   ncp pointer
 *
 */
static int __dump(ip *ncp)
{
        int ret = -1;
        int id = -1;

        if (unlikely(!ncp)) {
                ERROR("ncp is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP NCP %s BEGIN ---\n", ncp->name);

        /*dump ncp elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //NO subips

        /*end*/
        DEBUG("--- DUMP NCP %s END ---\n", ncp->name);

        ret = 0;
ret_dump:
        return ret;
}


/**
 * ops structure
 *
 */
static const ip_operations ncp_ops = {
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
        char *regconfig = "./configs/regconfig.ncp";
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
 * ncp_alloc - alloc ncp elements
 * @ncp:   pointer to ncp
 * @params:    init parameters
 *
 */
static int ncp_alloc(ip *ncp, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO need on ncp level!!!

        /*reg list*/
        if (unlikely(!params->ncp_reg_count)) {
                WARNING("have no register !!!\n");
        }

        //Trick: malloc(0)!=NULL
        ncp->reglist = malloc((params->ncp_reg_count + 1) * sizeof(regs *));
        if (unlikely(!ncp->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)ncp->reglist, 0, (params->ncp_reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->ncp_reg_count; id++) {
                ncp->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!ncp->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)ncp->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        ncp->name2reg = init_hashtable();
        if (unlikely(!ncp->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        ncp->addr2reg = init_hashtable();
        if (unlikely(!ncp->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
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
 * ncp_init - init ncp with params
 * @father:    pointer to the ncp belongs to
 * @ncp:        pointer to ncp
 * @id:        ncp id
 * @params:    init parameters
 *
 */
int ncp_init(ip *father, ip *ncp, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char *addr2str = NULL;

        /*begin*/
        INFO("NCP%d INIT\n", id);

        if (unlikely(!ncp) || unlikely(!params)) {
                ERROR("ncp is %p, params is %p\n", ncp, params);
                goto ret_init;
        }

        /*alloc*/
        ret = ncp_alloc(ncp, params);
        if (unlikely(ret)) {
                ERROR("ncp alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(ncp->name, "ncp%d", id);

        /*id*/
        ncp->id = id;

        /*state machine*/
        ncp->status = OFF;

        /*ops*/
        ncp->ops = &ncp_ops;

        /*memory*/
        //NO need on ncp level!!!

        /*reg list*/
        ret = parse_regconfig(ncp->reglist);
        if (unlikely(ret)) {
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->ncp_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(ncp->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(ncp->reglist[sub]->name,
                                (void *)ncp->reglist[sub],
                                ncp->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        ncp->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(ncp->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)ncp->reglist[sub], ncp->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        ncp->address = ncp->reglist;

        /*parent*/
        ncp->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        /*end*/
        INFO("NCP%d INIT DONE\n", id);

ret_init:
        return ret;
}
