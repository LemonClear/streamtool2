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
 * __on - core power on
 * @core: core pointer
 *
 */
static int __on(ip *core)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!core)) {
                ERROR("core is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- CORE %s POWER ON GO... -\n", core->name);

        /*core level do 1st*/
        //FIXME: todo...

        if (unlikely(!core->subips)) {
                ERROR("core->subips is null !!!\n");
                goto ret_on;
        }

        /*power on subips 2nd*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->poweron(core->subips[id]);
                if (unlikely(ret)) {
                        ERROR("poweron subip%d-%s failed !!!\n",
                                        id, core->subips[id]->name);
                        goto ret_on;
                }
                /*next subips*/
                id++;
        }

        /*change state machine third*/
        core->status = RUN;

        /*end*/
        INFO("- CORE %s POWER ON DONE -\n", core->name);

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
                ERROR("core is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- CORE %s POWER OFF GO... -\n", core->name);

        if (unlikely(!core->subips)) {
                ERROR("core->subips is null !!!\n");
                goto ret_off;
        }

        /*power off subips 1st*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->poweroff(core->subips[id]);
                if (unlikely(ret)) {
                        ERROR("poweroff subip%d-%s failed !!!\n",
                                        id, core->subips[id]->name);
                        goto ret_off;
                }
                /*next subips*/
                id++;
        }

        /*core level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        core->status = OFF;

        /*end*/
        INFO("- CORE %s POWER OFF DONE -\n", core->name);

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
                ERROR("core is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- CORE %s IDLE GO... -\n", core->name);

        if (unlikely(!core->subips)) {
                ERROR("core->subips is null !!!\n");
                goto ret_idle;
        }

        /*idle subips 1st*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->idle(core->subips[id]);
                if (unlikely(ret)) {
                        ERROR("idle subip%d-%s failed !!!\n",
                                        id, core->subips[id]->name);
                        goto ret_idle;
                }
                /*next subips*/
                id++;
        }

        /*core level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        core->status = IDLE;

        /*end*/
        INFO("- CORE %s IDLE DONE -\n", core->name);

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
                ERROR("core is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- CORE %s SLEEP GO... -\n", core->name);

        if (unlikely(!core->subips)) {
                ERROR("core->subips is null !!!\n");
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->sleep(core->subips[id]);
                if (unlikely(ret)) {
                        ERROR("sleep subip%d-%s failed !!!\n",
                                        id, core->subips[id]->name);
                        goto ret_sleep;
                }
                /*next subips*/
                id++;
        }

        /*core level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        core->status = SLEEP;

        /*end*/
        INFO("- CORE %s SLEEP DONE -\n", core->name);

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
                ERROR("core is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- CORE %s WAKEUP GO... -\n", core->name);

        /*core level do 1st*/
        //FIXME: todo...

        if (unlikely(!core->subips)) {
                ERROR("core->subips is null !!!\n");
                goto ret_wakeup;
        }

        /*wakeup subips 2nd*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->wakeup(core->subips[id]);
                if (unlikely(ret)) {
                        ERROR("wakeup subip%d-%s failed !!!\n",
                                        id, core->subips[id]->name);
                        goto ret_wakeup;
                }
                /*next subips*/
                id++;
        }

        /*change state machine third*/
        core->status = RUN;

        /*end*/
        INFO("- CORE %s WAKEUP DONE -\n", core->name);

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
                ERROR("core is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- CORE %s TICK %llu GO... -\n",
                        core->name, tick_counter);

        /*core level do 1st*/
        //FIXME: todo...

        if (unlikely(!core->subips)) {
                ERROR("core->subips is null !!!\n");
                goto ret_tick;
        }

        /*tick trigger subips 2nd*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->tickarrive(core->subips[id]);
                if (unlikely(ret)) {
                        ERROR("tick subip%d-%s failed !!!\n",
                                        id, core->subips[id]->name);
                        goto ret_tick;
                }
                /*next subips*/
                id++;
        }

        /*done*/
        INFO("- CORE %s TICK %llu DONE -\n",
                        core->name, tick_counter);

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

        if (unlikely(!core)) {
                ERROR("core is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP CORE %s BEGIN ---\n", core->name);

        /*dump core elements 1st*/
        //FIXME: todo...

        if (unlikely(!core->subips)) {
                ERROR("core->subips is null !!!\n");
                goto ret_dump;
        }

        /*dump subips 2nd*/
        while (core->subips[id]) {
                /*each subip*/
                ret = core->subips[id]->ops->dump(core->subips[id]);
                if (unlikely(ret)) {
                        ERROR("dump subip%d-%s failed !!!\n",
                                        id, core->subips[id]->name);
                        goto ret_dump;
                }
                /*next subips*/
                id++;
        }

        /*end*/
        DEBUG("--- DUMP CORE %s END ---\n", core->name);

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
                WARNING("have no registers !!!\n");
        }

        //Trick: malloc(0)!=NULL
        core->reglist = malloc((params->core_reg_count + 1) * sizeof(regs *));
        if (unlikely(!core->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)core->reglist, 0, (params->core_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->core_reg_count; id++) {
                core->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!core->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)core->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        core->name2reg = init_hashtable();
        if (unlikely(!core->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        core->addr2reg = init_hashtable();
        if (unlikely(!core->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
                goto ret_alloc;
        }

        /*subips list*/
        core->subips = malloc((params->ncp_count + params->tcp_count +
                                params->mcu_count + params->ram_count + 1) * sizeof(ip *));
        if (unlikely(!core->subips)) {
                ERROR("alloc subip array failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)core->subips, 0, (params->ncp_count + params->tcp_count +
                                params->mcu_count + params->ram_count + 1) * sizeof(ip *));

        for (id = 0; id < (params->ncp_count + params->tcp_count +
                                params->mcu_count + params->ram_count); id++) {
                core->subips[id] = malloc(sizeof(ip));
                if (unlikely(!core->subips[id])) {
                        ERROR("alloc subip%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)core->subips[id], 0, sizeof(ip));
        }

        /*subips hastable*/
        core->name2subip = init_hashtable();
        if (unlikely(!core->name2subip)) {
                ERROR("alloc hashtable name2subip failed !!!\n");
                goto ret_alloc;
        }

        core->addr2subip = init_hashtable();
        if (unlikely(!core->addr2subip)) {
                ERROR("alloc hashtable addr2subip failed !!!\n");
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
        INFO("- CORE core%d INIT GO... -\n", id);

        if (unlikely(!core) || unlikely(!params)) {
                ERROR("core is %p, params is %p\n",
                                core, params);
                goto ret_init;
        }

        /*alloc*/
        ret = core_alloc(core, params);
        if (unlikely(ret)) {
                ERROR("core alloc elements failed !!!\n");
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
                ERROR("reglist init failed !!!\n");
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
                        ERROR("hash %s to name2reg failed !!!\n",
                                        core->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", core->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)core->reglist[sub], core->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
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
                        ERROR("subip%d-ncp init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: tcp 2nd*/
        for (; sub < (params->ncp_count + params->tcp_count); sub++) {
                /*call subip:tcp init function*/
                ret = tcp_init(core, core->subips[sub], sub, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-tcp init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: mcu 3rd*/
        for (; sub < (params->ncp_count + params->tcp_count +
                                params->mcu_count); sub++) {
                /*call subip:mcu init function*/
                ret = mcu_init(core, core->subips[sub], sub, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-mcu init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: ram 4th*/
        for (; sub < (params->ncp_count + params->tcp_count +
                                params->mcu_count + params->ram_count); sub++) {
                /*call subip:ram init function*/
                ret = ram_init(core, core->subips[sub], sub, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-ram init failed !!!\n", sub);
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
                        ERROR("hash %s to name2subip failed !!!\n",
                                        core->subips[sub]->name);
                        goto ret_init;
                }

                /*table addr2subip*/
                sprintf(addr2str, "0x%x", core->subips[sub]->address);
                ret = insert_hashtable(addr2str, (void *)core->subips[sub],
                                core->addr2subip);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2subip failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*end*/
        INFO("- CORE core%d INIT DONE -\n", id);

ret_init:
        return ret;
}
