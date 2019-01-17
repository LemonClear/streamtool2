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
 * __on - noc power on
 * @noc:  noc pointer
 *
 */
static void __on(ip *noc)
{
        if (unlikely(!noc)) {
                printf("ERR: noc absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*noc level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        noc->status = RUN;

        printf("INFO: noc:%s power on!!!!! %s, %s, %d\n",
                        noc->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * __off - noc power off
 * @noc:   noc pointer
 *
 */
static void __off(ip *noc)
{
        if (unlikely(!noc)) {
                printf("ERR: noc absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //No subips

        /*noc level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        noc->status = OFF;

        printf("INFO: noc:%s power off!!!!! %s, %s, %d\n",
                        noc->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * __idle - noc idle
 * @noc:    noc pointer
 *
 */
static void __idle(ip *noc)
{
        if (unlikely(!noc)) {
                printf("ERR: noc absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //No subips

        /*noc level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        noc->status = IDLE;

        printf("INFO: noc:%s idle!!!!! %s, %s, %d\n",
                        noc->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * sleep - noc sleep
 * @noc:   noc pointer
 *
 */
static void __sleep(ip *noc)
{
        if (unlikely(!noc)) {
                printf("ERR: noc absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //No subips

        /*noc level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        noc->status = SLEEP;

        printf("INFO: noc:%s sleep!!!!! %s, %s, %d\n",
                        noc->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * __wakeup - noc wakeup
 * @noc:   noc pointer
 *
 */
static void __wakeup(ip *noc)
{
        if (unlikely(!noc)) {
                printf("ERR: noc absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*noc level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        noc->status = RUN;

        printf("INFO: noc:%s wakeup!!!!! %s, %s, %d\n",
                        noc->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * __tick - one tick trigger
 * @noc:    self pointer
 *
 */
static void __tick(ip *noc)
{
        if (unlikely(!noc)) {
                printf("ERR: noc absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: noc:%s tick:%llu come!!!!! %s, %s, %d\n",
                        noc->name, tick_counter, __FILE__, __func__, __LINE__);

        /*noc level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        printf("INFO: noc:%s tick:%llu done!!!!! %s, %s, %d\n",
                        noc->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * __dump - noc dump informations
 * @noc:  noc pointer
 *
 */
static void __dump(ip *noc)
{
        printf("DEBUG: ========== noc:%s dump start !!!!! ==========\n",
                        noc->name);

        if (unlikely(!noc)) {
                printf("ERR: noc absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump noc elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        printf("DEBUG: ========== noc:%s dump end !!!!! ==========\n",
                        noc->name);

ret_dump:
        return;
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
                printf("ERR: noc reglist absent! %s, %s, %d\n",
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
        if (!params->reg_count) { //FIXME: should separate ips reg count
                printf("INFO: noc have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL, if have no reg,
        //the noc->reglist value can also mark as this ip's address
        noc->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!noc->reglist)) {
                printf("ERR: alloc noc reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)noc->reglist, 0, (params->reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                noc->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!noc->reglist[id])) {
                        printf("ERR: alloc noc reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)noc->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        noc->name2reg = init_hashtable();
        if (unlikely(!noc->name2reg)) {
                printf("ERR: alloc noc reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        noc->addr2reg = init_hashtable();
        if (unlikely(!noc->addr2reg)) {
                printf("ERR: alloc noc reg hashtable failed! %s, %s, %d\n",
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
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: noc init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!noc) || unlikely(!params)) {
                printf("ERR: noc or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = noc_alloc(noc, params);
        if (unlikely(ret)) {
                printf("ERR: noc alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
                printf("ERR: noc reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(noc->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(noc->reglist[sub]->name,
                                (void *)noc->reglist[sub],
                                noc->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, noc->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", noc->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)noc->reglist[sub], noc->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, noc->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
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

        printf("INFO: noc init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
