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
 * @mcu:   mcu pointer
 *
 */
static int __on(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                printf("ERR: mcu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*mcu level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        mcu->status = RUN;

        printf("INFO: mcu:%s power on!!!!! %s, %s, %d\n",
                        mcu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - mcu power off
 * @mcu:    mcu pointer
 *
 */
static int __off(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                printf("ERR: mcu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //No subips

        /*mcu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        mcu->status = OFF;

        printf("INFO: mcu:%s power off!!!!! %s, %s, %d\n",
                        mcu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - mcu idle
 * @mcu:   mcu pointer
 *
 */
static int __idle(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                printf("ERR: mcu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //No subips

        /*mcu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        mcu->status = IDLE;

        printf("INFO: mcu:%s idle!!!!! %s, %s, %d\n",
                        mcu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - mcu sleep
 * @mcu:   mcu pointer
 *
 */
static int __sleep(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                printf("ERR: mcu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //No subips

        /*mcu level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        mcu->status = SLEEP;

        printf("INFO: mcu:%s sleep!!!!! %s, %s, %d\n",
                        mcu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - mcu wakeup
 * @mcu:   mcu pointer
 *
 */
static int __wakeup(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                printf("ERR: mcu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*mcu level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        mcu->status = RUN;

        printf("INFO: mcu:%s wakeup!!!!! %s, %s, %d\n",
                        mcu->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @mcu:   self pointer
 *
 */
static int __tick(ip *mcu)
{
        int ret = -1;

        if (unlikely(!mcu)) {
                printf("ERR: mcu absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: mcu:%s tick:%llu come!!!!! %s, %s, %d\n",
                        mcu->name, tick_counter, __FILE__, __func__, __LINE__);

        /*mcu level do 1st*/
        //FIXME: todo...

        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        printf("INFO: mcu:%s tick:%llu done!!!!! %s, %s, %d\n",
                        mcu->name, tick_counter, __FILE__, __func__, __LINE__);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - mcu dump informations
 * @mcu:   mcu pointer
 *
 */
static int __dump(ip *mcu)
{
        int ret = -1;

        printf("DEBUG: ========== mcu:%s dump start !!!!! ==========\n",
                        mcu->name);

        if (unlikely(!mcu)) {
                printf("ERR: mcu absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump mcu elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        printf("DEBUG: ========== mcu:%s dump end !!!!! ==========\n",
                        mcu->name);

        ret = 0;
ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations mcu_ops = {
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
        char *config = "./mcu.reg";

        if (unlikely(!reglist)) {
                printf("ERR: mcu reglist absent! %s, %s, %d\n",
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
 * mcu_alloc - alloc mcu elements
 * @mcu:   pointer to mcu
 * @params:    init parameters
 *
 */
static int mcu_alloc(ip *mcu, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        if (unlikely(!params->mcu_reg_count)) {
                printf("INFO: mcu have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        mcu->reglist = malloc((params->mcu_reg_count + 1) * sizeof(regs *));
        if (unlikely(!mcu->reglist)) {
                printf("ERR: alloc mcu reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)mcu->reglist, 0, (params->mcu_reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->mcu_reg_count; id++) {
                mcu->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!mcu->reglist[id])) {
                        printf("ERR: alloc mcu reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)mcu->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        mcu->name2reg = init_hashtable();
        if (unlikely(!mcu->name2reg)) {
                printf("ERR: alloc mcu reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        mcu->addr2reg = init_hashtable();
        if (unlikely(!mcu->addr2reg)) {
                printf("ERR: alloc mcu reg hashtable failed! %s, %s, %d\n",
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
 * mcu_init - init mcu with params
 * @father:    pointer to the mcu belongs to
 * @mcu:       pointer to mcu
 * @id:        mcu id
 * @params:    init parameters
 *
 */
int mcu_init(ip *father, ip *mcu, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char *addr2str = NULL;

        /*begin*/
        printf("INFO: mcu init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!mcu) || unlikely(!params)) {
                printf("ERR: mcu or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = mcu_alloc(mcu, params);
        if (unlikely(ret)) {
                printf("ERR: mcu alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(mcu->name, "mcu%d", id);

        /*id*/
        mcu->id = id;

        /*state machine*/
        mcu->status = OFF;

        /*ops*/
        mcu->ops = &mcu_ops;

        /*memory*/
        //FIXME: todo... maybe used as L2 cache? maybe no need.

        /*reg list*/
        ret = parse_regconfig(mcu->reglist);
        if (unlikely(ret)) {
                printf("ERR: mcu reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->mcu_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(mcu->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(mcu->reglist[sub]->name,
                                (void *)mcu->reglist[sub],
                                mcu->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, mcu->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(mcu->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)mcu->reglist[sub], mcu->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, mcu->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        mcu->address = mcu->reglist;

        /*parent*/
        mcu->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        printf("INFO: mcu init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
