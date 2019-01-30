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
#include <sys/types.h>
#include <sys/stat.h>
#include <malloc.h>
#include "common.h"
#include "of.h"
#include "logger.h"


/**
 * load_image_bd - load image to ddr through backdoor
 * @ddr:     self pointer
 * @offset:  image load offset from head of this ddr
 *
 * FIXME: maybe no need
 */
static int load_image_bd(ip *ddr, address32_t offset)
{
        int ret = -1;
        int id = -1;
        int fd = -1;
        int mem_size = -1;
        address32_t *mem_head = NULL;
        char *image = "./data/image";
 
        /*each ddr mem*/
        id = 0;
        while (ddr->memory[id]) {
                mem_head = ddr->memory[id];
                mem_size = malloc_usable_size(ddr->memory[id]);

                //FIXME: may load different image
                fd = open(image, O_RDONLY);
                if (unlikely(-1 == fd)) {
                        ERROR("open image file {%s} failed !!!\n", image);
                        goto ret_load;
                }

                //FIXME: todo...read, write

                /*next*/
                id++;
        }

        /*end*/
        ret = 0;

ret_load:
        return ret;
}


/**
 * __on - ddr power on
 * @ddr:  self pointer
 *
 */
static int __on(ip *ddr)
{
        int ret = -1;
        address32_t offset = 0;

        if (unlikely(!ddr)) {
                ERROR("ddr is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("DDR %s POWER ON\n", ddr->name);

        /*ddr level do 1st*/
        ret = load_image_bd(ddr, offset);
        if (unlikely(!ret)) {
                ERROR("load image backdoor failed !!!\n");
                goto ret_on;
        }
        //FIXME: todo...

        /*power on subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ddr->status = RUN;

        /*end*/
        INFO("DDR %s POWER ON DONE\n", ddr->name);

ret_on:
        return ret;
}


/**
 * __off - ddr power off
 * @ddr:   self pointer
 *
 */
static int __off(ip *ddr)
{
        int ret = -1;

        if (unlikely(!ddr)) {
                ERROR("ddr is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("DDR %s POWER OFF\n", ddr->name);

        /*power off subips 1st*/
        //NO subips

        /*ddr level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ddr->status = OFF;

        /*end*/
        INFO("DDR %s POWER OFF DONE\n", ddr->name);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - ddr idle
 * @ddr:    self pointer
 *
 */
static int __idle(ip *ddr)
{
        int ret = -1;

        if (unlikely(!ddr)) {
                ERROR("ddr is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("DDR %s IDLE\n", ddr->name);

        /*idle subips 1st*/
        //NO subips

        /*ddr level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ddr->status = IDLE;

        /*end*/
        INFO("DDR %s IDLE DONE\n", ddr->name);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - ddr sleep
 * @ddr:     self pointer
 *
 */
static int __sleep(ip *ddr)
{
        int ret = -1;

        if (unlikely(!ddr)) {
                ERROR("ddr is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("DDR %s SLEEP\n", ddr->name);

        /*sleep subips 1st*/
        //NO subips

        /*ddr level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ddr->status = SLEEP;

        /*end*/
        INFO("DDR %s SLEEP DONE\n", ddr->name);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - ddr wakeup
 * @ddr:      self pointer
 *
 */
static int __wakeup(ip *ddr)
{
        int ret = -1;

        if (unlikely(!ddr)) {
                ERROR("ddr is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("DDR %s WAKEUP\n", ddr->name);

        /*ddr level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ddr->status = RUN;

        /*end*/
        INFO("DDR %s WAKEUP DONE\n", ddr->name);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @ddr:    self pointer
 *
 */
static int __tick(ip *ddr)
{
        int ret = -1;

        if (unlikely(!ddr)) {
                ERROR("ddr is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("DDR %s TICK %llu\n",
                        ddr->name, tick_counter);

        /*ddr level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //NO subips

        /*end*/
        INFO("DDR %s TICK %llu DONE\n",
                        ddr->name, tick_counter);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - ddr dump informations
 * @ddr:  self pointer
 *
 */
static int __dump(ip *ddr)
{
        int ret = -1;

        if (unlikely(!ddr)) {
                ERROR("ddr is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP DDR %s BEGIN ---\n", ddr->name);

        /*dump ddr elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //NO subips

        /*end*/
        DEBUG("--- DUMP DDR %s END ---\n", ddr->name);

        ret = 0;
ret_dump:
        return ret;
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
 * parse_regconfig - parse regconfig file regconfig.xxx
 * @reglist:   pointer to reglist
 *
 */
static int parse_regconfig(regs **reglist)
{
        int ret = -1;
        char *regconfig = "./configs/regconfig.ddr";
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
                ERROR("alloc memory failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)ddr->memory, 0, (params->ddr_count + 1) * sizeof(address32_t *));

        for (id = 0; id < params->ddr_count; id++) {
                ddr->memory[id] = malloc(params->ddr_size); //ATT: memory[id]++ is 4bytes
                if (unlikely(!ddr->memory[id])) {
                        ERROR("alloc mem%d failed !!!\n", id);
                        goto ret_alloc;
                }
        }

        /*reg list*/
        if (unlikely(!params->ddr_reg_count)) {
                WARNING("have no registers !!!\n");
        }

        //Trick: malloc(0)!=NULL
        ddr->reglist = malloc((params->ddr_reg_count + 1) * sizeof(regs *));
        if (unlikely(!ddr->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)ddr->reglist, 0, (params->ddr_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->ddr_reg_count; id++) {
                ddr->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!ddr->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)ddr->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        ddr->name2reg = init_hashtable();
        if (unlikely(!ddr->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        ddr->addr2reg = init_hashtable();
        if (unlikely(!ddr->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
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
        char *addr2str = NULL;

        /*begin*/
        INFO("DDR%d INIT\n", id);

        if (unlikely(!ddr) || unlikely(!params)) {
                ERROR("ddr is %p, params is %p !!!\n",
                                ddr, params);
                goto ret_init;
        }

        /*alloc*/
        ret = ddr_alloc(ddr, params);
        if (unlikely(ret)) {
                ERROR("ddr alloc elements failed !!!\n");
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
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->ddr_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(ddr->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(ddr->reglist[sub]->name,
                                (void *)ddr->reglist[sub],
                                ddr->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        ddr->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(ddr->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)ddr->reglist[sub], ddr->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        ddr->address = ddr->reglist;

        /*parent*/
        ddr->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //NO subips

        /*subips: hashtable*/
        //NO subips

        /*end*/
        INFO("DDR%d INIT DONE\n", id);

ret_init:
        return ret;
}
