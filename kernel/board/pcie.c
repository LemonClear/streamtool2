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
 * __on - pcie power on
 * @pcie: pcie pointer
 *
 */
static void __on(ip *pcie)
{
        if (unlikely(!pcie)) {
                printf("ERR: pcie absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*pcie level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*change state machine 3rd*/
        pcie->status = RUN;

        printf("INFO: pcie:%s power on!!!!! %s, %s, %d\n",
                        pcie->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * __off - pcie power off
 * @pcie:  pcie pointer
 *
 */
static void __off(ip *pcie)
{
        if (unlikely(!pcie)) {
                printf("ERR: pcie absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*pcie level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        pcie->status = OFF;

        printf("INFO: pcie:%s power off!!!!! %s, %s, %d\n",
                        pcie->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * __idle - pcie idle
 * @pcie:   pcie pointer
 *
 */
static void __idle(ip *pcie)
{
        if (unlikely(!pcie)) {
                printf("ERR: pcie absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*pcie level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        pcie->status = IDLE;

        printf("INFO: pcie:%s idle!!!!! %s, %s, %d\n",
                        pcie->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * sleep - pcie sleep
 * @pcie:  pcie pointer
 *
 */
static void __sleep(ip *pcie)
{
        if (unlikely(!pcie)) {
                printf("ERR: pcie absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*pcie level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        pcie->status = SLEEP;

        printf("INFO: pcie:%s sleep!!!!! %s, %s, %d\n",
                        pcie->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * __wakeup - pcie wakeup
 * @pcie:   pcie pointer
 *
 */
static void __wakeup(ip *pcie)
{
        if (unlikely(!pcie)) {
                printf("ERR: pcie absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*pcie level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //FIXME: DO NOTHING!!!
        //No subips

        /*change state machine 3rd*/
        pcie->status = RUN;

        printf("INFO: pcie:%s wakeup!!!!! %s, %s, %d\n",
                        pcie->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * __tick - one tick trigger
 * @pcie:   self pointer
 *
 */
static void __tick(ip *pcie)
{
        if (unlikely(!pcie)) {
                printf("ERR: pcie absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: pcie:%s tick:%llu come!!!!! %s, %s, %d\n",
                        pcie->name, tick_counter, __FILE__, __func__, __LINE__);

        /*pcie level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        printf("INFO: pcie:%s tick:%llu done!!!!! %s, %s, %d\n",
                        pcie->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * __dump - pcie dump informations
 * @pcie:   pcie pointer
 *
 */
static void __dump(ip *pcie)
{
        printf("DEBUG: ========== pcie:%s dump start !!!!! ==========\n",
                        pcie->name);

        if (unlikely(!pcie)) {
                printf("ERR: pcie absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump pcie elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        printf("DEBUG: ========== pcie:%s dump end !!!!! ==========\n",
                        pcie->name);

ret_dump:
        return;
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
 * parse_regconfig - parse reg config file xxx.reg
 * @reglist:   pointer to reglist
 *
 * FIXME: to be replace by dt
 */
static int parse_regconfig(regs **reglist)
{
        int ret = -1;
        char *config = "./pcie.reg";

        if (unlikely(!reglist)) {
                printf("ERR: pcie reglist absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_config;
        }

        if (unlikely(access(config, F_OK))) {
                printf("WARN: config file %s absent! \
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
        if (!params->reg_count) { //FIXME: should separate ips reg count
                printf("INFO: pcie have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL, if have no reg,
        //the pcie->reglist value can also mark as this ip's address
        pcie->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!pcie->reglist)) {
                printf("ERR: alloc pcie reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)pcie->reglist, 0, (params->reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                pcie->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!pcie->reglist[id])) {
                        printf("ERR: alloc pcie reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)pcie->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        pcie->name2reg = init_hashtable();
        if (unlikely(!pcie->name2reg)) {
                printf("ERR: alloc pcie reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        pcie->addr2reg = init_hashtable();
        if (unlikely(!pcie->addr2reg)) {
                printf("ERR: alloc pcie reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: pcie init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!pcie) || unlikely(!params)) {
                printf("ERR: pcie or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = pcie_alloc(pcie, params);
        if (unlikely(ret)) {
                printf("ERR: pcie alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
                printf("ERR: pcie reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(pcie->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(pcie->reglist[sub]->name,
                                (void *)pcie->reglist[sub],
                                pcie->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, pcie->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", pcie->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)pcie->reglist[sub], pcie->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, pcie->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
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

        printf("INFO: pcie init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
