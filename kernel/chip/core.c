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
 * __on - core power on
 * @core: core pointer
 *
 */
static int __on(ip *core)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!core)) {
                printf("ERR: core absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*core level do 1st*/
        //FIXME: todo...

        if (unlikely(!core->subips)) {
                printf("ERR: core->subips absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*power on subips 2nd*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->poweron(core->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: poweron subip%d-%s failed! %s, %s, %d\n",
                                        id, core->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_on;
                }
                /*next subips*/
                id++;
        }

        /*change state machine third*/
        core->status = RUN;

        printf("INFO: core:%s power on!!!!! %s, %s, %d\n",
                        core->name, __FILE__, __func__, __LINE__);

ret_on:
        return ret;
}


/**
 * __off - core power off
 * @core:  core pointer
 *
 */
static int __off(ip *core)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!core)) {
                printf("ERR: core absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*begin*/
        if (unlikely(!core->subips)) {
                printf("ERR: core->subips absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->poweroff(core->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: poweroff subip%d-%s failed! %s, %s, %d\n",
                                        id, core->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_off;
                }
                /*next subips*/
                id++;
        }

        /*core level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        core->status = OFF;

        printf("INFO: core:%s power off!!!!! %s, %s, %d\n",
                        core->name, __FILE__, __func__, __LINE__);

ret_off:
        return ret;
}


/**
 * __idle - core idle
 * @core:   core pointer
 *
 */
static int __idle(ip *core)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!core)) {
                printf("ERR: core absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*begin*/
        if (unlikely(!core->subips)) {
                printf("ERR: core->subips absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->idle(core->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: idle subip%d-%s failed! %s, %s, %d\n",
                                        id, core->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_idle;
                }
                /*next subips*/
                id++;
        }

        /*core level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        core->status = IDLE;

        printf("INFO: core:%s idle!!!!! %s, %s, %d\n",
                        core->name, __FILE__, __func__, __LINE__);

ret_idle:
        return ret;
}


/**
 * __sleep - core sleep
 * @core:    core pointer
 *
 */
static int __sleep(ip *core)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!core)) {
                printf("ERR: core absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*begin*/
        if (unlikely(!core->subips)) {
                printf("ERR: core->subips absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->sleep(core->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: sleep subip%d-%s failed! %s, %s, %d\n",
                                        id, core->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_sleep;
                }
                /*next subips*/
                id++;
        }

        /*core level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        core->status = SLEEP;

        printf("INFO: core:%s sleep!!!!! %s, %s, %d\n",
                        core->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return ret;
}


/**
 * __wakeup - core wakeup
 * @core:     core pointer
 *
 */
static int __wakeup(ip *core)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!core)) {
                printf("ERR: core absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*core level do 1st*/
        //FIXME: todo...

        if (unlikely(!core->subips)) {
                printf("ERR: core->subips absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*wakeup subips 2nd*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->wakeup(core->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: wakeup subip%d-%s failed! %s, %s, %d\n",
                                        id, core->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_wakeup;
                }
                /*next subips*/
                id++;
        }

        /*change state machine third*/
        core->status = RUN;

        printf("INFO: core:%s wakeup!!!!! %s, %s, %d\n",
                        core->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @core:   self pointer
 *
 */
static int __tick(ip *core)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!core)) {
                printf("ERR: core absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: core:%s tick:%llu come!!!!! %s, %s, %d\n",
                        core->name, tick_counter, __FILE__, __func__, __LINE__);

        /*core level do 1st*/
        //FIXME: todo...

        if (unlikely(!core->subips)) {
                printf("ERR: core->subips absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*tick trigger subips 2nd*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->tickarrive(core->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: tick subip%d-%s failed! %s, %s, %d\n",
                                        id, core->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_tick;
                }
                /*next subips*/
                id++;
        }

        /*done*/
        printf("INFO: core:%s tick:%llu done!!!!! %s, %s, %d\n",
                        core->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return ret;
}


/**
 * __dump - core dump informations
 * @core:   core pointer
 *
 */
static int __dump(ip *core)
{
        int ret = -1;
        int id = 0;

        printf("DEBUG: ========== core:%s dump start !!!!! ==========\n",
                        core->name);

        if (unlikely(!core)) {
                printf("ERR: core absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump core elements 1st*/
        //FIXME: todo...

        if (unlikely(!core->subips)) {
                printf("ERR: core->subips absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump subips 2nd*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->dump(core->subips[id]);
                if (unlikely(ret)) {
                        printf("ERR: dump subip%d-%s failed! %s, %s, %d\n",
                                        id, core->subips[id]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_dump;
                }
                /*next subips*/
                id++;
        }

        printf("DEBUG: ========== core:%s dump end !!!!! ==========\n",
                        core->name);

ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations core_ops = {
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
        char *config = "./core.reg";

        if (unlikely(!reglist)) {
                printf("ERR: core reglist absent! %s, %s, %d\n",
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
 * core_alloc - alloc core elements
 * @core:    pointer to core
 * @params:  init parameters
 *
 */
static int core_alloc(ip *core, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO need on core level!!!

        /*reg list*/
        if (unlikely(!params->core_reg_count)) {
                printf("INFO: core have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        core->reglist = malloc((params->core_reg_count + 1) * sizeof(regs *));
        if (unlikely(!core->reglist)) {
                printf("ERR: alloc core reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)core->reglist, 0, (params->core_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->core_reg_count; id++) {
                core->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!core->reglist[id])) {
                        printf("ERR: alloc core reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)core->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        core->name2reg = init_hashtable();
        if (unlikely(!core->name2reg)) {
                printf("ERR: alloc core reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        core->addr2reg = init_hashtable();
        if (unlikely(!core->addr2reg)) {
                printf("ERR: alloc core reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        /*subips list*/
        core->subips = malloc((params->ncp_count + params->tcp_count +
                                params->mcu_count + params->ram_count + 1) * sizeof(ip *));
        if (unlikely(!core->subips)) {
                printf("ERR: core alloc subip array failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)core->subips, 0, (params->ncp_count + params->tcp_count +
                                params->mcu_count + params->ram_count + 1) * sizeof(ip *));

        for (id = 0; id < (params->ncp_count + params->tcp_count +
                                params->mcu_count + params->ram_count); id++) {
                core->subips[id] = malloc(sizeof(ip));
                if (unlikely(!core->subips[id])) {
                        printf("ERR: alloc core subip%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)core->subips[id], 0, sizeof(ip));
        }

        /*subips hastable*/
        core->name2subip = init_hashtable();
        if (unlikely(!core->name2subip)) {
                printf("ERR: alloc core subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        core->addr2subip = init_hashtable();
        if (unlikely(!core->addr2subip)) {
                printf("ERR: alloc core subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * core_init - init core with params
 * @father:    pointer to this core belongs to
 * @core:      pointer to core
 * @id:        core id
 * @params:    init parameters
 *
 */
int core_init(ip *father, ip *core, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: core init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!core) || unlikely(!params)) {
                printf("ERR: core or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = core_alloc(core, params);
        if (unlikely(ret)) {
                printf("ERR: core alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(core->name, "core%d", id);

        /*id*/
        core->id = id;

        /*state machine*/
        core->status = OFF;

        /*ops*/
        core->ops = &core_ops;

        /*memory*/
        //NO need on core level!!!

        /*reg list*/
        ret = parse_regconfig(core->reglist);
        if (unlikely(ret)) {
                printf("ERR: core reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->core_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(core->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(core->reglist[sub]->name,
                                (void *)core->reglist[sub],
                                core->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, core->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", core->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)core->reglist[sub], core->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, core->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        core->address = core->reglist;

        /*parent*/
        core->parent = father;

        /*connected*/
        //No connected

        /*subips: ncp 1st*/
        for (sub = 0; sub < params->ncp_count; sub++) {
                /*call subip:ncp init function*/
                ret = ncp_init(core, core->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-ncp init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: tcp 2nd*/
        for (; sub < (params->ncp_count + params->tcp_count); sub++) {
                /*call subip:tcp init function*/
                ret = tcp_init(core, core->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-tcp init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: mcu 3rd*/
        for (; sub < (params->ncp_count + params->tcp_count +
                                params->mcu_count); sub++) {
                /*call subip:mcu init function*/
                ret = mcu_init(core, core->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-mcu init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: ram 4th*/
        for (; sub < (params->ncp_count + params->tcp_count +
                                params->mcu_count + params->ram_count); sub++) {
                /*call subip:ram init function*/
                ret = ram_init(core, core->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-ram init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*subips: hashtable*/
        for (sub = 0; sub < (params->ncp_count + params->tcp_count +
                                params->mcu_count + params->ram_count); sub++) {
                /*bypass empty subip elements*/
                if (unlikely(!strcmp(core->subips[sub]->name, "")))
                        continue;

                /*table name2subip*/
                ret = insert_hashtable(core->subips[sub]->name,
                                (void *)core->subips[sub],
                                core->name2subip);
                if (unlikely(ret)) {
                        printf("ERR: hash %s to name2subip table failed! %s, %s, %d\n",
                                        core->subips[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2subip*/
                sprintf(addr2str, "0x%x", core->subips[sub]->address);
                ret = insert_hashtable(addr2str, (void *)core->subips[sub],
                                core->addr2subip);
                if (unlikely(ret)) {
                        printf("ERR: hash ncp/tcp/mcu/ram%d:0x%x to addr2subip \
                                        table failed! %s, %s, %d\n",
                                        sub, core->subips[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        printf("INFO: core init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
