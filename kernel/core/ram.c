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
 * load_image_bd - load image to ram through backdoor
 * @ram:     self pointer
 * @offset:  image load offset from head of this ram
 *
 * FIXME: maybe no need
 */
static int load_image_bd(ip *ram, address32_t offset)
{
        int ret = -1;
        int id = -1;
        int fd = -1;
        int mem_size = -1;
        address32_t *mem_head = NULL;
        char *image = "./data/image";

        /*each ram mem*/
        id = 0;
        while (ram->memory[id]) {
                mem_head = ram->memory[id];
                mem_size = malloc_usable_size(ram->memory[id]);

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
 * __on - ram power on
 * @ram:  self pointer
 *
 */
static int __on(ip *ram)
{
        int ret = -1;
        address32_t offset = 0;

        if (unlikely(!ram)) {
                ERROR("ram is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- RAM %s POWER ON GO>>> -\n", ram->name);

        /*ram level do 1st*/
        ret = load_image_bd(ram, offset);
        if (unlikely(!ret)) {
                ERROR("ram load image backdoor failed !!!\n");
                goto ret_on;
        }
        //FIXME: todo...

        /*power on subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ram->status = RUN;

        /*end*/
        INFO("- RAM %s POWER ON DONE -\n", ram->name);

ret_on:
        return ret;
}


/**
 * __off - ram power off
 * @ram:   self pointer
 *
 */
static int __off(ip *ram)
{
        int ret = -1;

        if (unlikely(!ram)) {
                ERROR("ram is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- RAM %s POWER OFF GO>>> -\n", ram->name);

        /*power off subips 1st*/
        //NO subips

        /*ram level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ram->status = OFF;

        /*end*/
        INFO("- RAM %s POWER OFF DONE -\n", ram->name);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - ram idle
 * @ram:    self pointer
 *
 */
static int __idle(ip *ram)
{
        int ret = -1;

        if (unlikely(!ram)) {
                ERROR("ram is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- RAM %s IDLE GO>>> -\n", ram->name);

        /*idle subips 1st*/
        //NO subips

        /*ram level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ram->status = IDLE;

        /*end*/
        INFO("- RAM %s IDLE DONE -\n", ram->name);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - ram sleep
 * @ram:     self pointer
 *
 */
static int __sleep(ip *ram)
{
        int ret = -1;

        if (unlikely(!ram)) {
                ERROR("ram is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- RAM %s SLEEP GO>>> -\n", ram->name);

        /*sleep subips 1st*/
        //NO subips

        /*ram level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ram->status = SLEEP;

        /*end*/
        INFO("- RAM %s SLEEP DONE -\n", ram->name);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - ram wakeup
 * @ram:      self pointer
 *
 */
static int __wakeup(ip *ram)
{
        int ret = -1;

        if (unlikely(!ram)) {
                ERROR("ram is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- RAM %s WAKEUP GO>>> -\n", ram->name);

        /*ram level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ram->status = RUN;

        /*end*/
        INFO("- RAM %s WAKEUP DONE -\n", ram->name);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __read - read data from memory
 * @ram:    self pointer
 * @start:  start address of memory to read
 * @length: bytes to read
 *
 */
static int __read(ip *ram, address32_t start, int length)
{
        int ret = -1;

ret_read:
        return ret;
}


/**
 * __write - write data to memory
 * @ram:    self pointer
 * @start:  start address of memory to write
 * @length: bytes to write
 *
 */
static int __write(ip *ram, address32_t start, int length)
{
        int ret = -1;

ret_write:
        return ret;
}


/**
 * __readreg - read ip registers
 * @ram:   pointer to ram
 * @addr:  register address
 * @name:  register name
 *
 */
static reg32_t __readreg(ip* ram, address32_t addr, char *name)
{
        reg32_t ret = 0;

        if (unlikely(!ram)) {
                ERROR("ram is null !!!\n");
                goto ret_readreg;
        }

        /*name == NULL, use addr*/
        if (likely(!name)) {
                ret = 0;
                goto ret_readreg;
        }

        /*name != NULL, use name*/
        WARNING("use register name to query !!!\n");


ret_readreg:
        return ret;
}


/**
 * __writereg - write ip registers
 * @addr:  register address
 * @name:  register name
 * @value: value to write
 *
 */
static int __writereg(ip *ram, address32_t addr, char *name, reg32_t value)
{
        int ret = -1;

        if (unlikely(!ram)) {
                ERROR("ram is null !!!\n");
                goto ret_writereg;
        }

        /*name == NULL, use addr*/
        if (likely(!name)) {
                ret = 0;
                goto ret_writereg;
        }

        /*name != NULL, use name*/
        WARNING("use register name to query !!!\n");


ret_writereg:
        return ret;
}


/**
 * __tick - one tick trigger
 * @ram:    self pointer
 *
 */
static int __tick(ip *ram)
{
        int ret = -1;

        if (unlikely(!ram)) {
                ERROR("ram is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- RAM %s TICK %llu GO>>> -\n",
                        ram->name, tick_counter);

        /*ram level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //NO subips

        /*done*/
        INFO("- RAM %s TICK %llu DONE -\n",
                        ram->name, tick_counter);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - ram dump informations
 * @ram:  self pointer
 *
 */
static int __dump(ip *ram)
{
        int ret = -1;

        if (unlikely(!ram)) {
                ERROR("ram is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP RAM %s BEGIN ---\n", ram->name);

        /*dump ram elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //NO subips

        /*end*/
        DEBUG("--- DUMP RAM %s END ---\n", ram->name);

        ret = 0;
ret_dump:
        return ret;
}


/**
 * ops structure
 *
 */
static const ip_operations ram_ops = {
        .poweron = __on,
        .poweroff = __off,
        .idle = __idle,
        .sleep = __sleep,
        .wakeup = __wakeup,
        .read = __read,
        .write = __write,
        .readreg = __readreg,
        .writereg = __writereg,
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
        char *regconfig = "./configs/regconfig.ram";
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
 * ram_alloc - alloc ram elements
 * @ram:       pointer to ram
 * @params:    init parameters
 *
 */
static int ram_alloc(ip *ram, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        ram->memory = malloc((params->ram_count + 1) * sizeof(address32_t *));
        if (unlikely(!ram->memory)) {
                ERROR("alloc memory failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)ram->memory, 0, (params->ram_count + 1) * sizeof(address32_t *));

        for (id = 0; id < params->ram_count; id++) {
                ram->memory[id] = malloc(params->ram_size); //ATT: memory[id]++ is 4bytes
                if (unlikely(!ram->memory[id])) {
                        ERROR("alloc mem%d failed !!!\n", id);
                        goto ret_alloc;
                }
        }

        /*reg list*/
        if (unlikely(!params->ram_reg_count))
                WARNING("have no register !!!\n");

        //Trick: malloc(0)!=NULL
        ram->reglist = malloc((params->ram_reg_count + 1) * sizeof(regs *));
        if (unlikely(!ram->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)ram->reglist, 0, (params->ram_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->ram_reg_count; id++) {
                ram->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!ram->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)ram->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        ram->name2reg = init_hashtable();
        if (unlikely(!ram->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        ram->addr2reg = init_hashtable();
        if (unlikely(!ram->addr2reg)) {
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
 * ram_init - init ram with params
 * @father:   pointer to the ram belongs to
 * @ram:      pointer to ram
 * @id:       ram id
 * @params:   init parameters
 *
 */
int ram_init(ip *father, ip *ram, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char *addr2str = NULL;

        /*begin*/
        INFO("- RAM ram%d INIT GO>>> -\n", id);

        if (unlikely(!ram) || unlikely(!params)) {
                ERROR("ram is %p, params is %p\n", ram, params);
                goto ret_init;
        }

        /*alloc*/
        ret = ram_alloc(ram, params);
        if (unlikely(ret)) {
                ERROR("ram alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(ram->name, "ram%d", id);

        /*id*/
        ram->id = id;

        /*state machine*/
        ram->status = OFF;

        /*ops*/
        ram->ops = &ram_ops;

        /*memory*/
        //FIXME: todo... maybe do nothing

        /*reg list*/
        ret = parse_regconfig(ram->reglist);
        if (unlikely(ret)) {
                ERROR("reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->ram_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(ram->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(ram->reglist[sub]->name,
                                (void *)ram->reglist[sub],
                                ram->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        ram->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(ram->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)ram->reglist[sub], ram->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        ram->address = ram->reglist;

        /*parent*/
        ram->parent = father;

        /*connected*/
        //NO connected

        /*subips: board 1st*/
        //NO subips

        /*subips: hashtable*/
        //NO subips

        /*end*/
        INFO("- RAM ram%d INIT DONE -\n", id);

ret_init:
        return ret;
}
