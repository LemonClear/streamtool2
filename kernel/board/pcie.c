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
 * __on - pcie power on
 * @pcie: pcie pointer
 *
 */
static int __on(ip *pcie)
{
        int ret = -1;

        if (unlikely(!pcie)) {
                ERROR("pcie is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("PCIE %s POWER ON\n", pcie->name);

        /*pcie level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*change state machine 3rd*/
        pcie->status = RUN;

        /*end*/
        INFO("PCIE %s POWER ON DONE\n", pcie->name);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - pcie power off
 * @pcie:  pcie pointer
 *
 */
static int __off(ip *pcie)
{
        int ret = -1;

        if (unlikely(!pcie)) {
                ERROR("pcie is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("PCIE %s POWER OFF\n", pcie->name);

        /*power off subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*pcie level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        pcie->status = OFF;

        /*end*/
        INFO("PCIE %s POWER OFF DONE\n", pcie->name);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - pcie idle
 * @pcie:   pcie pointer
 *
 */
static int __idle(ip *pcie)
{
        int ret = -1;

        if (unlikely(!pcie)) {
                ERROR("pcie is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("PCIE %s IDLE\n", pcie->name);

        /*idle subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*pcie level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        pcie->status = IDLE;

        /*end*/
        INFO("PCIE %s IDLE DONE\n", pcie->name);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * sleep - pcie sleep
 * @pcie:  pcie pointer
 *
 */
static int __sleep(ip *pcie)
{
        int ret = -1;

        if (unlikely(!pcie)) {
                ERROR("pcie is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("PCIE %s SLEEP\n", pcie->name);

        /*sleep subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*pcie level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        pcie->status = SLEEP;

        /*end*/
        INFO("PCIE %s SLEEP DONE\n", pcie->name);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - pcie wakeup
 * @pcie:   pcie pointer
 *
 */
static int __wakeup(ip *pcie)
{
        int ret = -1;

        if (unlikely(!pcie)) {
                ERROR("pcie is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("PCIE %s WAKEUP\n", pcie->name);

        /*pcie level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*change state machine 3rd*/
        pcie->status = RUN;

        /*end*/
        INFO("PCIE %s WAKEUP DONE\n", pcie->name);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @pcie:   self pointer
 *
 */
static int __tick(ip *pcie)
{
        int ret = -1;

        if (unlikely(!pcie)) {
                ERROR("pcie is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("PCIE %s TICK %llu\n",
                        pcie->name, tick_counter);

        /*pcie level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        INFO("PCIE %s TICK %llu DONE\n",
                        pcie->name, tick_counter);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - pcie dump informations
 * @pcie:   pcie pointer
 *
 */
static int __dump(ip *pcie)
{
        int ret = -1;


        if (unlikely(!pcie)) {
                ERROR("pcie is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP PCIE %s BEGIN ---\n", pcie->name);

        /*dump pcie elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        /*end*/
        DEBUG("--- DUMP PCIE %s END ---\n", pcie->name);

        ret = 0;
ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations pcie_ops = {
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
        char *regconfig = "./configs/regconfig.pcie";
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
 * pcie_alloc - alloc pcie elements
 * @pcie:    pointer to pcie
 * @params:  init parameters
 *
 */
static int pcie_alloc(ip *pcie, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO NEED on pcie level!!!

        /*reg list*/
        if (unlikely(!params->pcie_reg_count)) {
                WARNING("have no register !!!\n");
        }

        //Trick: malloc(0)!=NULL, if have no reg,
        //the pcie->reglist value can also mark as this ip's address
        pcie->reglist = malloc((params->pcie_reg_count + 1) * sizeof(regs *));
        if (unlikely(!pcie->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)pcie->reglist, 0, (params->pcie_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->pcie_reg_count; id++) {
                pcie->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!pcie->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)pcie->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        pcie->name2reg = init_hashtable();
        if (unlikely(!pcie->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        pcie->addr2reg = init_hashtable();
        if (unlikely(!pcie->addr2reg)) {
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
 * pcie_init - init pcie with params
 * @father:    pointer to the pcie belongs to
 * @pcie:      pointer to pcie
 * @id:        pcie id
 * @params:    init parameters
 *
 */
int pcie_init(ip *father, ip *pcie, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char *addr2str = NULL;

        /*begin*/
        INFO("PCIE%d INIT\n", id);

        if (unlikely(!pcie) || unlikely(!params)) {
                ERROR("pcie is %p, params is %p !!!\n",
                                pcie, params);
                goto ret_init;
        }

        /*alloc*/
        ret = pcie_alloc(pcie, params);
        if (unlikely(ret)) {
                ERROR("pcie alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(pcie->name, "pcie%d", id);

        /*id*/
        pcie->id = id;

        /*state machine*/
        pcie->status = OFF;

        /*ops*/
        pcie->ops = &pcie_ops;

        /*memory*/
        //NO NEED on pcie level!!!

        /*reg list*/
        ret = parse_regconfig(pcie->reglist);
        if (unlikely(ret)) {
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->pcie_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(pcie->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(pcie->reglist[sub]->name,
                                (void *)pcie->reglist[sub],
                                pcie->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        pcie->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(pcie->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)pcie->reglist[sub], pcie->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        pcie->address = pcie->reglist;

        /*parent*/
        pcie->parent = father;

        /*connected*/
        //No connected

        /*subips*/
        //No subips

        /*subips: hashtable*/
        //No subips

        /*end*/
        INFO("PCIE%d INIT DONE\n", id);

ret_init:
        return ret;
}
