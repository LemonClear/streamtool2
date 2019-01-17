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
                        printf("ERR: open image file:%s failed, please check! %s, %s, %d\n",
                                        image, __FILE__, __func__, __LINE__);
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
static void __on(ip *ram)
{
        int ret = -1;
        address32_t offset = 0;

        /*begin*/
        if (unlikely(!ram)) {
                printf("ERR: ram absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*ram level do 1st*/
        ret = load_image_bd(ram, offset);
        if (unlikely(!ret)) {
                printf("ERR: ram load image backdoor failed, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }
        //FIXME: todo...

        /*power on subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ram->status = RUN;

        /*end*/
        printf("INFO: ram:%s power on!!!!! %s, %s, %d\n",
                        ram->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * __off - ram power off
 * @ram:   self pointer
 *
 */
static void __off(ip *ram)
{
        if (unlikely(!ram)) {
                printf("ERR: ram absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //NO subips

        /*ram level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ram->status = OFF;

        printf("INFO: ram:%s power off!!!!! %s, %s, %d\n",
                        ram->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * __idle - ram idle
 * @ram:    self pointer
 *
 */
static void __idle(ip *ram)
{
        if (unlikely(!ram)) {
                printf("ERR: ram absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //NO subips

        /*ram level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ram->status = IDLE;

        printf("INFO: ram:%s idle!!!!! %s, %s, %d\n",
                        ram->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * __sleep - ram sleep
 * @ram:     self pointer
 *
 */
static void __sleep(ip *ram)
{
        if (unlikely(!ram)) {
                printf("ERR: ram absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //NO subips

        /*ram level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        ram->status = SLEEP;

        printf("INFO: ram:%s sleep!!!!! %s, %s, %d\n",
                        ram->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * __wakeup - ram wakeup
 * @ram:      self pointer
 *
 */
static void __wakeup(ip *ram)
{
        if (unlikely(!ram)) {
                printf("ERR: ram absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*ram level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //NO subips

        /*change state machine 3rd*/
        ram->status = RUN;

        printf("INFO: ram:%s wakeup!!!!! %s, %s, %d\n",
                        ram->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * __read - read data from memory
 * @ram:    self pointer
 * @start:  start address of memory to read
 * @length: bytes to read
 *
 */
static void __read(ip *ram, address32_t start, int length)
{

}


/**
 * __write - write data to memory
 * @ram:    self pointer
 * @start:  start address of memory to write
 * @length: bytes to write
 *
 */
static void __write(ip *ram, address32_t start, int length)
{

}


/**
 * __tick - one tick trigger
 * @ram:    self pointer
 *
 */
static void __tick(ip *ram)
{
        if (unlikely(!ram)) {
                printf("ERR: ram absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: ram:%s tick:%llu come!!!!! %s, %s, %d\n",
                        ram->name, tick_counter, __FILE__, __func__, __LINE__);

        /*ram level do 1st*/
        //FIXME: todo...


        /*tick trigger subips 2nd*/
        //NO subips

        /*done*/
        printf("INFO: ram:%s tick:%llu done!!!!! %s, %s, %d\n",
                        ram->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * __dump - ram dump informations
 * @ram:  self pointer
 *
 */
static void __dump(ip *ram)
{
        printf("DEBUG: ========== ram:%s dump start !!!!! ==========\n",
                        ram->name);

        if (unlikely(!ram)) {
                printf("ERR: ram absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump ram elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //NO subips

        printf("DEBUG: ========== ram:%s dump end !!!!! ==========\n",
                        ram->name);

ret_dump:
        return;
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
        char *config = "./ram.reg";

        if (unlikely(!reglist)) {
                printf("ERR: ram reglist absent! %s, %s, %d\n",
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
                printf("ERR: alloc ram memory failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)ram->memory, 0, (params->ram_count + 1) * sizeof(address32_t *));

        for (id = 0; id < params->ram_count; id++) {
                ram->memory[id] = malloc(params->ram_size); //ATT: memory[id]++ is 4bytes
                if (unlikely(!ram->memory[id])) {
                        printf("ERR: alloc ram mem%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
        }

        /*reg list*/
        if (unlikely(!params->reg_count)) { //FIXME: should separate ips reg count
                printf("INFO: ram have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        ram->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!ram->reglist)) {
                printf("ERR: alloc ram reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)ram->reglist, 0, (params->reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                ram->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!ram->reglist[id])) {
                        printf("ERR: alloc ram reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)ram->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        ram->name2reg = init_hashtable();
        if (unlikely(!ram->name2reg)) {
                printf("ERR: alloc ram reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        ram->addr2reg = init_hashtable();
        if (unlikely(!ram->addr2reg)) {
                printf("ERR: alloc ram reg hashtable failed! %s, %s, %d\n",
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
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: ram init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!ram) || unlikely(!params)) {
                printf("ERR: ram or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = ram_alloc(ram, params);
        if (unlikely(ret)) {
                printf("ERR: ram alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
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
                printf("ERR: ram reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(ram->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(ram->reglist[sub]->name,
                                (void *)ram->reglist[sub],
                                ram->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, ram->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", ram->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)ram->reglist[sub], ram->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, ram->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
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

        printf("INFO: ram init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
