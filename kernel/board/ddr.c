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
#include <malloc.h>
#include "common.h"
#include "of.h"


/**
 * load_image - load image to ddr
 * @ddr:  self pointer
 *
 * FIXME: no need here, move to ram inside core
 *
 */
static int load_image(ip *ddr, address32_t offset, int length)
{
        int ret = -1;
        int mem_size = -1;
        int id = -1;
        int fd = -1;
        char *image = "./data/image";
 
        //FIXME: todo...
        id = 0;
        while (ddr->memory[id]) {
                mem_size = malloc_usable_size(ddr->memory[id]);

                fd = open(image, O_RDONLY);

                id++;
        }

ret_load:
        return ret;
}


/**
 * __on - ddr power on
 * @ddr:  self pointer
 *
 */
static void __on(ip *ddr)
{
        if (unlikely(!ddr)) {
                printf("ERR: ddr absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*ddr level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ddr->status = RUN;

        printf("INFO: ddr:%s power on!!!!! %s, %s, %d\n",
                        ddr->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * __off - ddr power off
 * @ddr:   self pointer
 *
 */
static void __off(ip *ddr)
{
        if (unlikely(!ddr)) {
                printf("ERR: ddr absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //NO subips

        /*ddr level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ddr->status = OFF;

        printf("INFO: ddr:%s power off!!!!! %s, %s, %d\n",
                        ddr->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * __idle - ddr idle
 * @ddr:    self pointer
 *
 */
static void __idle(ip *ddr)
{
        if (unlikely(!ddr)) {
                printf("ERR: ddr absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //NO subips

        /*ddr level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ddr->status = IDLE;

        printf("INFO: ddr:%s idle!!!!! %s, %s, %d\n",
                        ddr->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * __sleep - ddr sleep
 * @ddr:     self pointer
 *
 */
static void __sleep(ip *ddr)
{
        if (unlikely(!ddr)) {
                printf("ERR: ddr absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //NO subips

        /*ddr level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ddr->status = SLEEP;

        printf("INFO: ddr:%s sleep!!!!! %s, %s, %d\n",
                        ddr->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * __wakeup - ddr wakeup
 * @ddr:      self pointer
 *
 */
static void __wakeup(ip *ddr)
{
        if (unlikely(!ddr)) {
                printf("ERR: ddr absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*ddr level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ddr->status = RUN;

        printf("INFO: ddr:%s wakeup!!!!! %s, %s, %d\n",
                        ddr->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * __tick - one tick trigger
 * @ddr:    self pointer
 *
 */
static void __tick(ip *ddr)
{
        if (unlikely(!ddr)) {
                printf("ERR: ddr absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: ddr:%s tick:%llu come!!!!! %s, %s, %d\n",
                        ddr->name, tick_counter, __FILE__, __func__, __LINE__);

        /*ddr level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //NO subips

        /*done*/
        printf("INFO: ddr:%s tick:%llu done!!!!! %s, %s, %d\n",
                        ddr->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * __dump - ddr dump informations
 * @ddr:  self pointer
 *
 */
static void __dump(ip *ddr)
{
        printf("DEBUG: ========== ddr:%s dump start !!!!! ==========\n",
                        ddr->name);

        if (unlikely(!ddr)) {
                printf("ERR: ddr absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump ddr elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //NO subips

        printf("DEBUG: ========== ddr:%s dump end !!!!! ==========\n",
                        ddr->name);

ret_dump:
        return;
}
/**
 * ops structure
 *
 */
static const ip_operations ddr_ops = {
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
        char *config = "./ddr.reg";

        if (unlikely(!reglist)) {
                printf("ERR: ddr reglist absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_config;
        }

        //FIXME: todo...

ret_config:
        return ret;
}


/**
 * ddr_alloc - alloc ddr elements
 * @ddr:       pointer to ddr
 * @params:    init parameters
 *
 */
static int ddr_alloc(ip *ddr, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        ddr->memory = malloc((params->ddr_count + 1) * sizeof(address32_t *));
        if (unlikely(!ddr->memory)) {
                printf("ERR: alloc ddr memory failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)ddr->memory, 0, (params->ddr_count + 1) * sizeof(address32_t *));

        for (id = 0; id < params->ddr_count; id++) {
                ddr->memory[id] = malloc(params->ddr_size); //ATT: memory[id]++ is 4bytes
                if (unlikely(!ddr->memory[id])) {
                        printf("ERR: alloc ddr mem%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
        }

        /*reg list*/
        if (!params->reg_count) { //FIXME: should separate ips reg count
                printf("INFO: ddr have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        ddr->reglist = malloc(params->reg_count * sizeof(regs *));
        if (unlikely(!ddr->reglist)) {
                printf("ERR: alloc ddr reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)ddr->reglist, 0, params->reg_count * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                ddr->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!ddr->reglist[id])) {
                        printf("ERR: alloc ddr reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)ddr->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        ddr->name2reg = init_hashtable();
        if (unlikely(!ddr->name2reg)) {
                printf("ERR: alloc ddr reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        ddr->addr2reg = init_hashtable();
        if (unlikely(!ddr->addr2reg)) {
                printf("ERR: alloc ddr reg hashtable failed! %s, %s, %d\n",
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
 * ddr_init - init ddr with params
 * @father:   pointer to the ddr belongs to
 * @ddr:      pointer to ddr
 * @id:       ddr id
 * @params:   init parameters
 *
 */
int ddr_init(ip *father, ip *ddr, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: ddr init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!ddr) || unlikely(!params)) {
                printf("ERR: ddr or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = ddr_alloc(ddr, params);
        if (unlikely(ret)) {
                printf("ERR: ddr alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(ddr->name, "ddr%d", id);

        /*id*/
        ddr->id = id;

        /*state machine*/
        ddr->status = OFF;

        /*ops*/
        ddr->ops = &ddr_ops;

        /*memory*/
        //FIXME: todo... maybe do nothing

        /*reg list*/
        ret = parse_regconfig(ddr->reglist);
        if (unlikely(ret)) {
                printf("ERR: ddr reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(ddr->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(ddr->reglist[sub]->name,
                                (void *)ddr->reglist[sub],
                                ddr->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, ddr->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", ddr->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)ddr->reglist[sub], ddr->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, ddr->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        ddr->address = ddr->reglist;

        /*parent*/
        ddr->parent = father;

        /*connected*/
        ddr->east = NULL;
        ddr->west = NULL;
        ddr->sourth = NULL;
        ddr->north = NULL;

        /*subips: board 1st*/
        //NO subips

        /*subips: hashtable*/
        //NO subips

        printf("INFO: ddr init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
