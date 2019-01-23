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
 * __on - tcp power on
 * @tcp:   tcp pointer
 *
 */
static int __on(ip *tcp)
{
        int ret = -1;

        if (unlikely(!tcp)) {
                printf("ERR: tcp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*tcp level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        tcp->status = RUN;

        printf("INFO: tcp:%s power on!!!!! %s, %s, %d\n",
                        tcp->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_on:
        return ret;
}


/**
 * __off - tcp power off
 * @tcp:    tcp pointer
 *
 */
static int __off(ip *tcp)
{
        int ret = -1;

        if (unlikely(!tcp)) {
                printf("ERR: tcp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips 1st*/
        //No subips

        /*tcp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        tcp->status = OFF;

        printf("INFO: tcp:%s power off!!!!! %s, %s, %d\n",
                        tcp->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_off:
        return ret;
}


/**
 * __idle - tcp idle
 * @tcp:   tcp pointer
 *
 */
static int __idle(ip *tcp)
{
        int ret = -1;

        if (unlikely(!tcp)) {
                printf("ERR: tcp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips 1st*/
        //No subips

        /*tcp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        tcp->status = IDLE;

        printf("INFO: tcp:%s idle!!!!! %s, %s, %d\n",
                        tcp->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_idle:
        return ret;
}


/**
 * __sleep - tcp sleep
 * @tcp:   tcp pointer
 *
 */
static int __sleep(ip *tcp)
{
        int ret = -1;

        if (unlikely(!tcp)) {
                printf("ERR: tcp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        //No subips

        /*tcp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        tcp->status = SLEEP;

        printf("INFO: tcp:%s sleep!!!!! %s, %s, %d\n",
                        tcp->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_sleep:
        return ret;
}


/**
 * __wakeup - tcp wakeup
 * @tcp:   tcp pointer
 *
 */
static int __wakeup(ip *tcp)
{
        int ret = -1;

        if (unlikely(!tcp)) {
                printf("ERR: tcp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*tcp level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        tcp->status = RUN;

        printf("INFO: tcp:%s wakeup!!!!! %s, %s, %d\n",
                        tcp->name, __FILE__, __func__, __LINE__);

        ret = 0;
ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @tcp:     self pointer
 *
 */
static int __tick(ip *tcp)
{
        int ret = -1;

        if (unlikely(!tcp)) {
                printf("ERR: tcp absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: tcp:%s tick:%llu come!!!!! %s, %s, %d\n",
                        tcp->name, tick_counter, __FILE__, __func__, __LINE__);

        /*tcp level do 1st*/
        //FIXME: todo...

        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        printf("INFO: tcp:%s tick:%llu done!!!!! %s, %s, %d\n",
                        tcp->name, tick_counter, __FILE__, __func__, __LINE__);

        ret = 0;
ret_tick:
        return ret;
}


/**
 * __dump - tcp dump informations
 * @tcp:   tcp pointer
 *
 */
static int __dump(ip *tcp)
{
        int ret = -1;
        int id = 0;

        printf("DEBUG: ========== tcp:%s dump start !!!!! ==========\n",
                        tcp->name);

        if (unlikely(!tcp)) {
                printf("ERR: tcp absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump tcp elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        printf("DEBUG: ========== tcp:%s dump end !!!!! ==========\n",
                        tcp->name);

        ret = 0;
ret_dump:
        return ret;
}


/**
 * ops structure
 *
 */
static const ip_operations tcp_ops = {
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
        char *config = "./tcp.reg";

        if (unlikely(!reglist)) {
                printf("ERR: tcp reglist absent! %s, %s, %d\n",
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
 * tcp_alloc - alloc tcp elements
 * @tcp:       pointer to tcp
 * @params:   init parameters
 *
 */
static int tcp_alloc(ip *tcp, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO need on tcp level!!!

        /*reg list*/
        if (unlikely(!params->tcp_reg_count)) { //FIXME: should separate ips reg count
                printf("INFO: tcp have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        //Trick: malloc(0)!=NULL
        tcp->reglist = malloc((params->tcp_reg_count + 1) * sizeof(regs *));
        if (unlikely(!tcp->reglist)) {
                printf("ERR: alloc tcp reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)tcp->reglist, 0, (params->tcp_reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->tcp_reg_count; id++) {
                tcp->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!tcp->reglist[id])) {
                        printf("ERR: alloc tcp reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)tcp->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        tcp->name2reg = init_hashtable();
        if (unlikely(!tcp->name2reg)) {
                printf("ERR: alloc tcp reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        tcp->addr2reg = init_hashtable();
        if (unlikely(!tcp->addr2reg)) {
                printf("ERR: alloc tcp reg hashtable failed! %s, %s, %d\n",
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
 * tcp_init - init tcp with params
 * @father:   pointer to the tcp belongs to
 * @tcp:       pointer to tcp
 * @id:       tcp id
 * @params:   init parameters
 *
 */
int tcp_init(ip *father, ip *tcp, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: tcp init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!tcp) || unlikely(!params)) {
                printf("ERR: tcp or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = tcp_alloc(tcp, params);
        if (unlikely(ret)) {
                printf("ERR: tcp alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(tcp->name, "tcp%d", id);

        /*id*/
        tcp->id = id;

        /*state machine*/
        tcp->status = OFF;

        /*ops*/
        tcp->ops = &tcp_ops;

        /*memory*/
        //NO need on tcp level!!!

        /*reg list*/
        ret = parse_regconfig(tcp->reglist);
        if (unlikely(ret)) {
                printf("ERR: tcp reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->tcp_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(tcp->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(tcp->reglist[sub]->name,
                                (void *)tcp->reglist[sub],
                                tcp->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, tcp->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", tcp->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)tcp->reglist[sub], tcp->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, tcp->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        tcp->address = tcp->reglist;

        /*parent*/
        tcp->parent = father;

        /*connected*/
        //No connected

        /*subips: board 1st*/
        //No subips

        /*subips: hashtable*/
        //No subips

        printf("INFO: tcp init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
