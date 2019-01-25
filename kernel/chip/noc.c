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
 * __on - noc power on
 * @noc:  noc pointer
 *
 */
static int __on(ip *noc)
{
        int ret = -1;

        if (unlikely(!noc)) {
                ERROR("noc is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- NOC %s POWER ON GO... -\n", noc->name);

        /*noc level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        noc->status = RUN;

        /*end*/
        INFO("- NOC %s POWER ON DONE -\n", noc->name);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - noc power off
 * @noc:   noc pointer
 *
 */
static int __off(ip *noc)
{
        int ret = -1;

        if (unlikely(!noc)) {
                ERROR("noc is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- NOC %s POWER OFF GO... -\n", noc->name);

        /*power off subips 1st*/
        //No subips

        /*noc level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        noc->status = OFF;

        /*end*/
        INFO("- NOC %s POWER OFF DONE -\n", noc->name);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - noc idle
 * @noc:    noc pointer
 *
 */
static int __idle(ip *noc)
{
        int ret = -1;

        if (unlikely(!noc)) {
                ERROR("noc is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- NOC %s IDLE GO... -\n", noc->name);

        /*idle subips 1st*/
        //No subips

        /*noc level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        noc->status = IDLE;

        /*end*/
        INFO("- NOC %s IDLE DONE -\n", noc->name);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * sleep - noc sleep
 * @noc:   noc pointer
 *
 */
static int __sleep(ip *noc)
{
        int ret = -1;

        if (unlikely(!noc)) {
                ERROR("noc is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- NOC %s SLEEP GO... -\n", noc->name);

        /*sleep subips 1st*/
        //No subips

        /*noc level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        noc->status = SLEEP;

        /*end*/
        INFO("- NOC %s SLEEP DONE -\n", noc->name);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - noc wakeup
 * @noc:   noc pointer
 *
 */
static int __wakeup(ip *noc)
{
        int ret = -1;

        if (unlikely(!noc)) {
                ERROR("noc is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- NOC %s WAKEUP GO... -\n", noc->name);

        /*noc level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        noc->status = RUN;

        /*end*/
        INFO("- NOC %s WAKEUP DONE -\n", noc->name);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @noc:    self pointer
 *
 */
static int __tick(ip *noc)
{
        int ret = -1;

        if (unlikely(!noc)) {
                ERROR("noc is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- NOC %s TICK %llu GO... -\n",
                        noc->name, tick_counter);

        /*noc level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        INFO("- NOC %s TICK %llu DONE -\n",
                        noc->name, tick_counter);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - noc dump informations
 * @noc:  noc pointer
 *
 */
static int __dump(ip *noc)
{
        int ret = -1;

        if (unlikely(!noc)) {
                ERROR("noc is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP NOC %s BEGIN ---\n", noc->name);

        /*dump noc elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        /*end*/
        DEBUG("--- DUMP NOC %s END ---\n", noc->name);

        ret = 0;
ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations noc_ops = {
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
        char *config = "./noc.reg";

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
 * noc_alloc - alloc noc elements
 * @noc:     pointer to noc
 * @params:  init parameters
 *
 */
static int noc_alloc(ip *noc, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO need on noc level!!!

        /*reg list*/
        if (unlikely(!params->noc_reg_count)) {
                WARNING("have no register !!!\n");
        }

        //Trick: malloc(0)!=NULL, if have no reg,
        //the noc->reglist value can also mark as this ip's address
        noc->reglist = malloc((params->noc_reg_count + 1) * sizeof(regs *));
        if (unlikely(!noc->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)noc->reglist, 0, (params->noc_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->noc_reg_count; id++) {
                noc->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!noc->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)noc->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        noc->name2reg = init_hashtable();
        if (unlikely(!noc->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        noc->addr2reg = init_hashtable();
        if (unlikely(!noc->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
                goto ret_alloc;
        }

        /*subips list*/
        //NO subips

        /*subips hastable*/
        //No subips

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * noc_init - init noc with params
 * @father:    pointer to the noc belongs to
 * @noc:       pointer to noc
 * @id:        noc id
 * @params:    init parameters
 *
 */
int noc_init(ip *father, ip *noc, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char *addr2str = NULL;

        /*begin*/
        INFO("- NOC noc%d INIT GO... -\n", id);

        if (unlikely(!noc) || unlikely(!params)) {
                ERROR("noc is %p, params is %p !!!\n",
                                noc, params);
                goto ret_init;
        }

        /*alloc*/
        ret = noc_alloc(noc, params);
        if (unlikely(ret)) {
                ERROR("noc alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(noc->name, "noc%d", id);

        /*id*/
        noc->id = id;

        /*state machine*/
        noc->status = OFF;

        /*ops*/
        noc->ops = &noc_ops;

        /*memory*/
        //NO need on noc level!!!

        /*reg list*/
        ret = parse_regconfig(noc->reglist);
        if (unlikely(ret)) {
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->noc_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(noc->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(noc->reglist[sub]->name,
                                (void *)noc->reglist[sub],
                                noc->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        noc->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(noc->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)noc->reglist[sub], noc->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        noc->address = noc->reglist;

        /*parent*/
        noc->parent = father;

        /*connected*/
        //No connected

        /*subips: noc 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        /*end*/
        INFO("- NOC noc%d INIT DONE -\n", id);

ret_init:
        return ret;
}
