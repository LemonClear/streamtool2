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
 * __on - ncp power on
 * @ncp:   ncp pointer
 *
 */
static int __on(ip *ncp)
{
        int ret = -1;

        if (unlikely(!ncp)) {
                printf("ERR: ncp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*ncp level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ncp->status = RUN;

        printf("INFO: ncp:%s power on!!!!! %s, %s, %d\n",
                        ncp->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: ncp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //NO subips

        /*ncp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ncp->status = OFF;

        printf("INFO: ncp:%s power off!!!!! %s, %s, %d\n",
                        ncp->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: ncp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //NO subips

        /*ncp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ncp->status = IDLE;

        printf("INFO: ncp:%s idle!!!!! %s, %s, %d\n",
                        ncp->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: ncp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //NO subips

        /*ncp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ncp->status = SLEEP;

        printf("INFO: ncp:%s sleep!!!!! %s, %s, %d\n",
                        ncp->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: ncp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*ncp level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ncp->status = RUN;

        printf("INFO: ncp:%s wakeup!!!!! %s, %s, %d\n",
                        ncp->name, __FILE__, __func__, __LINE__);

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
                printf("ERR: ncp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: ncp:%s tick:%llu come!!!!! %s, %s, %d\n",
                        ncp->name, tick_counter, __FILE__, __func__, __LINE__);

        /*ncp level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //NO subips

        /*done*/
        printf("INFO: ncp:%s tick:%llu done!!!!! %s, %s, %d\n",
                        ncp->name, tick_counter, __FILE__, __func__, __LINE__);

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

        printf("DEBUG: ========== ncp:%s dump start !!!!! ==========\n",
                        ncp->name);

        if (unlikely(!ncp)) {
                printf("ERR: ncp absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump ncp elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //NO subips

        printf("DEBUG: ========== ncp:%s dump end !!!!! ==========\n",
                        ncp->name);

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
 * parse_regconfig - parse reg config file xxx.reg
 * @reglist:   pointer to reglist
 *
 * FIXME: to be replace by dt
 */
static int parse_regconfig(regs **reglist)
{
        int ret = -1;
        char *config = "./ncp.reg";

        if (unlikely(!reglist)) {
                printf("ERR: ncp reglist absent! %s, %s, %d\n",
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
        if (unlikely(!params->ncp_reg_count)) { //FIXME: should separate ips reg count
                printf("INFO: ncp have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        ncp->reglist = malloc((params->ncp_reg_count + 1) * sizeof(regs *));
        if (unlikely(!ncp->reglist)) {
                printf("ERR: alloc ncp reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)ncp->reglist, 0, (params->ncp_reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->ncp_reg_count; id++) {
                ncp->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!ncp->reglist[id])) {
                        printf("ERR: alloc ncp reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)ncp->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        ncp->name2reg = init_hashtable();
        if (unlikely(!ncp->name2reg)) {
                printf("ERR: alloc ncp reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        ncp->addr2reg = init_hashtable();
        if (unlikely(!ncp->addr2reg)) {
                printf("ERR: alloc ncp reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: ncp init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!ncp) || unlikely(!params)) {
                printf("ERR: ncp or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = ncp_alloc(ncp, params);
        if (unlikely(ret)) {
                printf("ERR: ncp alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
                printf("ERR: ncp reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, ncp->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", ncp->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)ncp->reglist[sub], ncp->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, ncp->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
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

        printf("INFO: ncp init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
