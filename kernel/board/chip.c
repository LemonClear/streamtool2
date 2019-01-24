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
 * __on - chip power on
 * @chip: chip pointer
 *
 */
static int __on(ip *chip)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!chip)) {
                ERROR("chip is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- CHIP %s POWER ON GO... -\n", chip->name);

        /*chip level do 1st*/
        //FIXME: todo...

        /*chip have no subip*/
        if (unlikely(!chip->subips)) {
                ERROR("chip->subips is null !!!\n");
                goto ret_on;
        }

        /*power on subips 2nd*/
        while (chip->subips[id]) {
                /*each subip*/
                ret = chip->subips[id]->ops->poweron(chip->subips[id]);
                if (unlikely(ret)) {
                        ERROR("poweron subip%d-%s failed !!!\n",
                                        id, chip->subips[id]->name);
                        goto ret_on;
                }
                /*next subip*/
                id++;
        }

        /*change state machine third*/
        chip->status = RUN;

        /*end*/
        INFO("- CHIP %s POWER ON DONE -\n", chip->name);

ret_on:
        return ret;
}


/**
 * __off - chip power off
 * @chip:  chip pointer
 *
 */
static int __off(ip *chip)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!chip)) {
                ERROR("chip is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- CHIP %s POWER OFF GO... -\n", chip->name);

        /*chip have no subip*/
        if (unlikely(!chip->subips)) {
                ERROR("chip->subips is null !!!\n");
                goto ret_off;
        }

        /*power off subips 1st*/
        while (chip->subips[id]) {
                /*each subip*/
                ret = chip->subips[id]->ops->poweroff(chip->subips[id]);
                if (unlikely(ret)) {
                        ERROR("poweroff subip%d-%s failed !!!\n",
                                        id, chip->subips[id]->name);
                        goto ret_off;
                }
                /*next subip*/
                id++;
        }

        /*chip level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        chip->status = OFF;

        /*end*/
        INFO("- CHIP %s POWER OFF DONE -\n", chip->name);

ret_off:
        return ret;
}


/**
 * __idle - chip idle
 * @chip:   chip pointer
 *
 */
static int __idle(ip *chip)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!chip)) {
                ERROR("chip is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- CHIP %s IDLE GO... -\n", chip->name);

        /*chip have no subip*/
        if (unlikely(!chip->subips)) {
                ERROR("chip->subips is null !!!\n");
                goto ret_idle;
        }

        /*idle subips 1st*/
        while (chip->subips[id]) {
                /*each subip*/
                ret = chip->subips[id]->ops->idle(chip->subips[id]);
                if (unlikely(ret)) {
                        ERROR("idle subip%d-%s failed !!!\n",
                                        id, chip->subips[id]->name);
                        goto ret_idle;
                }
                /*next subip*/
                id++;
        }

        /*chip level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        chip->status = IDLE;

        /*end*/
        INFO("- CHIP %s IDLE DONE -\n", chip->name);

ret_idle:
        return ret;
}


/**
 * __sleep - chip sleep
 * @chip:    chip pointer
 *
 */
static int __sleep(ip *chip)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!chip)) {
                ERROR("chip is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- CHIP %s SLEEP GO... -\n", chip->name);

        /*chip have no subip*/
        if (unlikely(!chip->subips)) {
                ERROR("chip->subips is null !!!\n");
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        while (chip->subips[id]) {
                /*each subip*/
                ret = chip->subips[id]->ops->sleep(chip->subips[id]);
                if (unlikely(ret)) {
                        ERROR("sleep subip%d-%s failed !!!\n",
                                        id, chip->subips[id]->name);
                        goto ret_sleep;
                }
                /*next subip*/
                id++;
        }

        /*chip level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        chip->status = SLEEP;

        /*end*/
        INFO("- CHIP %s SLEEP DONE -\n", chip->name);

ret_sleep:
        return ret;
}


/**
 * __wakeup - chip wakeup
 * @chip:     chip pointer
 *
 */
static int __wakeup(ip *chip)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!chip)) {
                ERROR("chip is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- CHIP %s WAKEUP GO... -\n", chip->name);

        /*chip level do 1st*/
        //FIXME: todo...

        /*chip have no subip*/
        if (unlikely(!chip->subips)) {
                ERROR("chip->subips is null !!!\n");
                goto ret_wakeup;
        }

        /*wakeup subips 2nd*/
        while (chip->subips[id]) {
                /*each subip*/
                ret = chip->subips[id]->ops->wakeup(chip->subips[id]);
                if (unlikely(ret)) {
                        ERROR("wakeup subip%d-%s failed !!!\n",
                                        id, chip->subips[id]->name);
                        goto ret_wakeup;
                }
                /*next subip*/
                id++;
        }

        /*change state machine third*/
        chip->status = RUN;

        /*end*/
        INFO("- CHIP %s WAKEUP DONE -\n", chip->name);

ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @chip:   self pointer
 *
 */
static int __tick(ip *chip)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!chip)) {
                ERROR("chip is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- CHIP %s TICK %llu GO... -\n",
                        chip->name, tick_counter);

        /*chip level do 1st*/
        //FIXME: todo...

        /*chip have no subip*/
        if (unlikely(!chip->subips)) {
                ERROR("chip->subips is null !!!\n");
                goto ret_tick;
        }

        /*tick trigger subips 2nd*/
        while (chip->subips[id]) {
                /*each subip*/
                ret = chip->subips[id]->ops->tickarrive(chip->subips[id]);
                if (unlikely(ret)) {
                        ERROR("tick subip%d-%s failed !!!\n",
                                        id, chip->subips[id]->name);
                        goto ret_tick;
                }
                /*next subip*/
                id++;
        }

        /*done*/
        INFO("- CHIP %s TICK %llu DONE -\n",
                        chip->name, tick_counter);

ret_tick:
        return ret;
}


/**
 * __dump - chip dump informations
 * @chip:   chip pointer
 *
 */
static int __dump(ip *chip)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!chip)) {
                ERROR("chip is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP CHIP %s BEGIN ---\n", chip->name);

        /*dump chip elements 1st*/
        //FIXME: todo...

        /*chip have no subip*/
        if (unlikely(!chip->subips)) {
                ERROR("chip->subips is null !!!\n");
                goto ret_dump;
        }

        /*dump subips 2nd*/
        while (chip->subips[id]) {
                /*each subip*/
                ret = chip->subips[id]->ops->dump(chip->subips[id]);
                if (unlikely(ret)) {
                        ERROR("dump subip%d-%s failed !!!\n",
                                        id, chip->subips[id]->name);
                        goto ret_dump;
                }
                /*next subip*/
                id++;
        }

        /*end*/
        DEBUG("--- DUMP CHIP %s END ---\n", chip->name);

ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations chip_ops = {
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
        char *config = "./chip.reg";

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
 * chip_alloc - alloc chip elements
 * @chip:    pointer to chip
 * @params:  init parameters
 *
 */
static int chip_alloc(ip *chip, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //FIXME: DO NOTHING!!!
        //NO NEED on chip level!!!

        /*reg list*/
        if (unlikely(!params->chip_reg_count)) {
                WARNING("have no regster !!!\n");
        }

        //Trick: malloc(0)!=NULL
        chip->reglist = malloc((params->chip_reg_count + 1) * sizeof(regs *));
        if (unlikely(!chip->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)chip->reglist, 0, (params->chip_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->chip_reg_count; id++) {
                chip->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!chip->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)chip->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        chip->name2reg = init_hashtable();
        if (unlikely(!chip->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        chip->addr2reg = init_hashtable();
        if (unlikely(!chip->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
                goto ret_alloc;
        }

        /*subips list*/
        chip->subips = malloc((params->core_count +
                                params->noc_count + 1) * sizeof(ip *));
        if (unlikely(!chip->subips)) {
                ERROR("alloc subip array failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)chip->subips, 0, (params->core_count +
                                params->noc_count + 1) * sizeof(ip *));

        for (id = 0; id < (params->core_count +
                                params->noc_count); id++) {
                chip->subips[id] = malloc(sizeof(ip));
                if (unlikely(!chip->subips[id])) {
                        ERROR("alloc subip%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)chip->subips[id], 0, sizeof(ip));
        }

        /*subips hastable*/
        chip->name2subip = init_hashtable();
        if (unlikely(!chip->name2subip)) {
                ERROR("alloc hashtable name2subip failed !!!\n");
                goto ret_alloc;
        }

        chip->addr2subip = init_hashtable();
        if (unlikely(!chip->addr2subip)) {
                ERROR("alloc hashtable addr2subip failed !!!\n");
                goto ret_alloc;
        }

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * chip_init - init chip with params
 * @father:    pointer to the chip belongs to
 * @chip:      pointer to chip
 * @id:        chip id
 * @params:    init parameters
 *
 */
int chip_init(ip *father, ip *chip, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        INFO("- CHIP chip%d INIT GO... -\n", id);

        if (unlikely(!chip) || unlikely(!params)) {
                ERROR("chip is %p, params is %p !!!\n", chip, params);
                goto ret_init;
        }

        /*alloc*/
        ret = chip_alloc(chip, params);
        if (unlikely(ret)) {
                ERROR("chip alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(chip->name, "chip%d", id);

        /*id*/
        chip->id = id;

        /*state machine*/
        chip->status = OFF;

        /*ops*/
        chip->ops = &chip_ops;

        /*memory*/
        //FIXME: DO NOTHING!!!
        //NO NEED on chip level!!!

        /*reg list*/
        ret = parse_regconfig(chip->reglist);
        if (unlikely(ret)) {
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->chip_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(chip->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(chip->reglist[sub]->name,
                                (void *)chip->reglist[sub],
                                chip->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        chip->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", chip->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)chip->reglist[sub], chip->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        chip->address = chip->reglist;

        /*parent*/
        chip->parent = father;

        /*connected*/
        //No connected

        /*subips: core 1st*/
        for (sub = 0; sub < params->core_count; sub++) {
                /*call subip:core init function*/
                ret = core_init(chip, chip->subips[sub], sub, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-core init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: noc 2nd*/
        for (; sub < (params->core_count + params->noc_count); sub++) {
                /*call subip:noc init function*/
                ret = noc_init(chip, chip->subips[sub], sub, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-noc init failed !!!\n",sub);
                        goto ret_init;
                }
        }

        /*subips: hashtable*/
        for (sub = 0; sub < (params->core_count +
                                params->noc_count); sub++) {
                /*bypass empty subip elements*/
                if (unlikely(!strcmp(chip->subips[sub]->name, "")))
                        continue;

                /*table name2subip*/
                ret = insert_hashtable(chip->subips[sub]->name,
                                (void *)chip->subips[sub],
                                chip->name2subip);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2subip failed !!!\n",
                                        chip->subips[sub]->name);
                        goto ret_init;
                }

                /*table addr2subip*/
                sprintf(addr2str, "0x%x", chip->subips[sub]->address);
                ret = insert_hashtable(addr2str, (void *)chip->subips[sub],
                                chip->addr2subip);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2subip failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*end*/
        INFO("- CHIP chip%d INIT DONE -\n", id);

ret_init:
        return ret;
}
