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
 * __on - chip power on
 * @chip: chip pointer
 *
 */
static void __on(ip *chip)
{
        int id = 0;

        if (unlikely(!chip)) {
                printf("ERR: chip absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*chip level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        while (chip->subips[id]) {
                /*each subip*/
                chip->subips[id]->ops->poweron(chip->subips[id]);

                id++;
        }

        /*change state machine third*/
        chip->status = RUN;

        printf("INFO: chip:%s power on!!!!! %s, %s, %d\n",
                        chip->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * __off - chip power off
 * @chip:  chip pointer
 *
 */
static void __off(ip *chip)
{
        int id = 0;

        if (unlikely(!chip)) {
                printf("ERR: chip absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        while (chip->subips[id]) {
                /*each subip*/
                chip->subips[id]->ops->poweroff(chip->subips[id]);

                id++;
        }

        /*chip level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        chip->status = OFF;

        printf("INFO: chip:%s power off!!!!! %s, %s, %d\n",
                        chip->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * __idle - chip idle
 * @chip:   chip pointer
 *
 */
static void __idle(ip *chip)
{
        int id = 0;

        if (unlikely(!chip)) {
                printf("ERR: chip absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        while (chip->subips[id]) {
                /*each subip*/
                chip->subips[id]->ops->idle(chip->subips[id]);

                id++;
        }

        /*chip level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        chip->status = IDLE;

        printf("INFO: chip:%s idle!!!!! %s, %s, %d\n",
                        chip->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * __sleep - chip sleep
 * @chip:    chip pointer
 *
 */
static void __sleep(ip *chip)
{
        int id = 0;

        if (unlikely(!chip)) {
                printf("ERR: chip absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        while (chip->subips[id]) {
                /*each subip*/
                chip->subips[id]->ops->sleep(chip->subips[id]);

                id++;
        }

        /*chip level do 2nd*/
        //FIXME: todo...

        /*change state machine third*/
        chip->status = SLEEP;

        printf("INFO: chip:%s sleep!!!!! %s, %s, %d\n",
                        chip->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * __wakeup - chip wakeup
 * @chip:     chip pointer
 *
 */
static void __wakeup(ip *chip)
{
        int id = 0;

        if (unlikely(!chip)) {
                printf("ERR: chip absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*chip level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        while (chip->subips[id]) {
                /*each subip*/
                chip->subips[id]->ops->wakeup(chip->subips[id]);

                id++;
        }

        /*change state machine third*/
        chip->status = RUN;

        printf("INFO: chip:%s wakeup!!!!! %s, %s, %d\n",
                        chip->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * __tick - one tick trigger
 * @chip:   self pointer
 *
 */
static void __tick(ip *chip)
{
        int id = 0;

        if (unlikely(!chip)) {
                printf("ERR: chip absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: chip:%s tick:%llu come!!!!! %s, %s, %d\n",
                        chip->name, tick_counter, __FILE__, __func__, __LINE__);

        /*chip level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        while (chip->subips[id]) {
                /*each subip*/
                chip->subips[id]->ops->tickarrive(chip->subips[id]);

                id++;
        }

        /*done*/
        printf("INFO: chip:%s tick:%llu done!!!!! %s, %s, %d\n",
                        chip->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * __dump - chip dump informations
 * @chip:   chip pointer
 *
 */
static void __dump(ip *chip)
{
        int id = 0;

        printf("DEBUG: ========== chip:%s dump start !!!!! ==========\n",
                        chip->name);

        if (unlikely(!chip)) {
                printf("ERR: chip absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump chip elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        while (chip->subips[id]) {
                /*each subip*/
                chip->subips[id]->ops->dump(chip->subips[id]);

                id++;
        }

        printf("DEBUG: ========== chip:%s dump end !!!!! ==========\n",
                        chip->name);

ret_dump:
        return;
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
                printf("ERR: chip reglist absent! %s, %s, %d\n",
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
        if (!params->reg_count) { //FIXME: should separate ips reg count
                printf("INFO: chip have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        chip->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!chip->reglist)) {
                printf("ERR: alloc chip reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)chip->reglist, 0, (params->reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                chip->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!chip->reglist[id])) {
                        printf("ERR: alloc chip reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)chip->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        chip->name2reg = init_hashtable();
        if (unlikely(!chip->name2reg)) {
                printf("ERR: alloc chip reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        chip->addr2reg = init_hashtable();
        if (unlikely(!chip->addr2reg)) {
                printf("ERR: alloc chip reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        /*subips list*/
        chip->subips = malloc((params->core_count +
                                params->noc_count + 1) * sizeof(ip *));
        if (unlikely(!chip->subips)) {
                printf("ERR: chip alloc subip array failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)chip->subips, 0, (params->core_count +
                                params->noc_count + 1) * sizeof(ip *));

        for (id = 0; id < (params->core_count +
                                params->noc_count); id++) {
                chip->subips[id] = malloc(sizeof(ip));
                if (unlikely(!chip->subips[id])) {
                        printf("ERR: alloc chip subip%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)chip->subips[id], 0, sizeof(ip));
        }

        /*subips hastable*/
        chip->name2subip = init_hashtable();
        if (unlikely(!chip->name2subip)) {
                printf("ERR: alloc chip subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        chip->addr2subip = init_hashtable();
        if (unlikely(!chip->addr2subip)) {
                printf("ERR: alloc chip subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
        printf("INFO: chip init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!chip) || unlikely(!params)) {
                printf("ERR: chip or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = chip_alloc(chip, params);
        if (unlikely(ret)) {
                printf("ERR: chip alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
                printf("ERR: chip reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(chip->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(chip->reglist[sub]->name,
                                (void *)chip->reglist[sub],
                                chip->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, chip->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", chip->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)chip->reglist[sub], chip->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, chip->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
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
                        printf("ERR: subip%d-core init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: noc 2nd*/
        for (; sub < (params->core_count + params->noc_count); sub++) {
                /*call subip:noc init function*/
                ret = noc_init(chip, chip->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-noc init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
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
                        printf("ERR: hash %s to name2subip table failed! %s, %s, %d\n",
                                        chip->subips[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2subip*/
                sprintf(addr2str, "0x%x", chip->subips[sub]->address);
                ret = insert_hashtable(addr2str, (void *)chip->subips[sub],
                                chip->addr2subip);
                if (unlikely(ret)) {
                        printf("ERR: hash chip/noc%d:0x%x to addr2subip table failed! %s, %s, %d\n",
                                        sub, chip->subips[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        printf("INFO: chip init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
