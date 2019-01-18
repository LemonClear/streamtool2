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
 * __on - main control cpu power on
 * @maincpu:   maincpu pointer
 *
 */
static int __on(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                printf("ERR: maincpu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*maincpu level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        maincpu->status = RUN;

        printf("INFO: maincpu:%s power on!!!!! %s, %s, %d\n",
                        maincpu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - maincpu power off
 * @maincpu:   maincpu pointer
 *
 */
static int __off(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                printf("ERR: maincpu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //No subips

        /*maincpu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        maincpu->status = OFF;

        printf("INFO: maincpu:%s power off!!!!! %s, %s, %d\n",
                        maincpu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - maincpu idle
 * @maincpu:   maincpu pointer
 *
 */
static int __idle(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                printf("ERR: maincpu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //No subips

        /*maincpu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        maincpu->status = IDLE;

        printf("INFO: maincpu:%s idle!!!!! %s, %s, %d\n",
                        maincpu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - maincpu sleep
 * @maincpu:   maincpu pointer
 *
 */
static int __sleep(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                printf("ERR: maincpu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //No subips

        /*maincpu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        maincpu->status = SLEEP;

        printf("INFO: maincpu:%s sleep!!!!! %s, %s, %d\n",
                        maincpu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - maincpu wakeup
 * @maincpu:   maincpu pointer
 *
 */
static int __wakeup(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                printf("ERR: maincpu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*maincpu level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        maincpu->status = RUN;

        printf("INFO: maincpu:%s wakeup!!!!! %s, %s, %d\n",
                        maincpu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @maincpu:   self pointer
 *
 */
static int __tick(ip *maincpu)
{
        int ret = -1;

        if (unlikely(!maincpu)) {
                printf("ERR: maincpu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: maincpu:%s tick:%llu come!!!!! %s, %s, %d\n",
                        maincpu->name, tick_counter, __FILE__, __func__, __LINE__);

        /*maincpu level do 1st*/
        //FIXME: todo...

        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        printf("INFO: maincpu:%s tick:%llu done!!!!! %s, %s, %d\n",
                        maincpu->name, tick_counter, __FILE__, __func__, __LINE__);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - maincpu dump informations
 * @maincpu:   maincpu pointer
 *
 */
static int __dump(ip *maincpu)
{
        int ret = -1;

        printf("DEBUG: ========== maincpu:%s dump start !!!!! ==========\n",
                        maincpu->name);

        if (unlikely(!maincpu)) {
                printf("ERR: maincpu absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump maincpu elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        printf("DEBUG: ========== maincpu:%s dump end !!!!! ==========\n",
                        maincpu->name);

        ret = 0;
ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations maincpu_ops = {
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
        char *config = "./maincpu.reg";

        if (unlikely(!reglist)) {
                printf("ERR: maincpu reglist absent! %s, %s, %d\n",
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
 * maincpu_alloc - alloc maincpu elements
 * @maincpu:   pointer to maincpu
 * @params:    init parameters
 *
 */
static int maincpu_alloc(ip *maincpu, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        if (unlikely(!params->reg_count)) { //FIXME: should separate ips reg count
                printf("INFO: maincpu have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        maincpu->reglist = malloc((params->reg_count + 1) * sizeof(regs *));
        if (unlikely(!maincpu->reglist)) {
                printf("ERR: alloc maincpu reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)maincpu->reglist, 0, (params->reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                maincpu->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!maincpu->reglist[id])) {
                        printf("ERR: alloc maincpu reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)maincpu->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        maincpu->name2reg = init_hashtable();
        if (unlikely(!maincpu->name2reg)) {
                printf("ERR: alloc maincpu reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        maincpu->addr2reg = init_hashtable();
        if (unlikely(!maincpu->addr2reg)) {
                printf("ERR: alloc maincpu reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        /*subips list*/
        //No subips

        /*subips hastable*/
        //No subips

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * maincpu_init - init maincpu with params
 * @father:    pointer to the maincpu belongs to
 * @maincpu:   pointer to maincpu
 * @id:        maincpu id
 * @params:    init parameters
 *
 */
int maincpu_init(ip *father, ip *maincpu, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: maincpu init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!maincpu) || unlikely(!params)) {
                printf("ERR: maincpu or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = maincpu_alloc(maincpu, params);
        if (unlikely(ret)) {
                printf("ERR: maincpu alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(maincpu->name, "maincpu%d", id);

        /*id*/
        maincpu->id = id;

        /*state machine*/
        maincpu->status = OFF;

        /*ops*/
        maincpu->ops = &maincpu_ops;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        ret = parse_regconfig(maincpu->reglist);
        if (unlikely(ret)) {
                printf("ERR: maincpu reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(maincpu->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(maincpu->reglist[sub]->name,
                                (void *)maincpu->reglist[sub],
                                maincpu->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, maincpu->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", maincpu->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)maincpu->reglist[sub], maincpu->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, maincpu->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        maincpu->address = maincpu->reglist;

        /*parent*/
        maincpu->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        printf("INFO: maincpu init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
