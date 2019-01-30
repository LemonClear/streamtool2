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
 * __on - tcp power on
 * @tcp:   tcp pointer
 *
 */
static int __on(ip *tcp)
{
        int ret = -1;

        if (unlikely(!tcp)) {
                ERROR("tcp is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- TCP %s POWER ON GO>>> -\n", tcp->name);

        /*tcp level do 1st*/
        //FIXME: todo...

        /*power on subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        tcp->status = RUN;

        /*end*/
        INFO("- TCP %s POWER ON DONE -\n", tcp->name);

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
                ERROR("tcp is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- TCP %s POWER OFF GO>>> -\n", tcp->name);

        /*power off subips 1st*/
        //No subips

        /*tcp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        tcp->status = OFF;

        /*end*/
        INFO("- TCP %s POWER OFF DONE -\n", tcp->name);

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
                ERROR("tcp is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- TCP %s IDLE GO>>> -\n", tcp->name);

        /*idle subips 1st*/
        //No subips

        /*tcp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        tcp->status = IDLE;

        /*end*/
        INFO("- TCP %s IDLE DONE -\n", tcp->name);

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
                ERROR("tcp is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- TCP %s SLEEP GO>>> -\n", tcp->name);

        /*sleep subips 1st*/
        //No subips

        /*tcp level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        tcp->status = SLEEP;

        /*end*/
        INFO("- TCP %s SLEEP DONE -\n", tcp->name);

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
                ERROR("tcp is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- TCP %s WAKEUP GO>>> -\n", tcp->name);

        /*tcp level do 1st*/
        //FIXME: todo...

        /*wakeup subips 2nd*/
        //No subips

        /*change state machine 3rd*/
        tcp->status = RUN;

        /*end*/
        INFO("- TCP %s WAKEUP DONE -\n", tcp->name);

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
                ERROR("tcp is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- TCP %s TICK %llu GO>>> -\n",
                        tcp->name, tick_counter);

        /*tcp level do 1st*/
        //FIXME: todo...

        /*tick trigger subips 2nd*/
        //No subips

        /*done*/
        INFO("- TCP %s TICK %llu DONE -\n",
                        tcp->name, tick_counter);

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

        if (unlikely(!tcp)) {
                ERROR("tcp is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP TCP %s BEGIN ---\n", tcp->name);

        /*dump tcp elements 1st*/
        //FIXME: todo...

        /*dump subips 2nd*/
        //No subips

        /*end*/
        DEBUG("--- DUMP TCP %s END ---\n", tcp->name);

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
 * parse_regconfig - parse regconfig file regconfig.xxx
 * @reglist:   pointer to reglist
 *
 */
static int parse_regconfig(regs **reglist)
{
        int ret = -1;
        char *regconfig = "./configs/regconfig.tcp";
        char delimit = 0;

        INFO("- PARSE REGCONFIG {%s} GO>>> -\n", regconfig);

        if (unlikely(!reglist)) {
                ERROR("reglist is null !!!\n");
                goto ret_config;
        }

        ret = of_regconfig(regconfig, reglist, delimit);
        if (unlikely(ret)) {
                ERROR("parse regconfig file {%s} failed !!!\n", regconfig);
                goto ret_config;
        }

        INFO("- PARSE REGCONFIG {%s} DONE -\n", regconfig);

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
        if (unlikely(!params->tcp_reg_count)) {
                WARNING("have no register !!!\n");
        }

        //Trick: malloc(0)!=NULL
        tcp->reglist = malloc((params->tcp_reg_count + 1) * sizeof(regs *));
        if (unlikely(!tcp->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)tcp->reglist, 0, (params->tcp_reg_count + 1 ) * sizeof(regs *));

        for (id = 0; id < params->tcp_reg_count; id++) {
                tcp->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!tcp->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)tcp->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        tcp->name2reg = init_hashtable();
        if (unlikely(!tcp->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        tcp->addr2reg = init_hashtable();
        if (unlikely(!tcp->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
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
        char *addr2str = NULL;

        /*begin*/
        INFO("- TCP tcp%d INIT GO>>> -\n", id);

        if (unlikely(!tcp) || unlikely(!params)) {
                ERROR("tcp is %p, params is %p\n", tcp, params);
                goto ret_init;
        }

        /*alloc*/
        ret = tcp_alloc(tcp, params);
        if (unlikely(ret)) {
                ERROR("tcp alloc elements failed !!!\n");
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
                ERROR("reglist init failed !!!\n");
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
                        ERROR("hash %s to name2reg failed !!!\n",
                                        tcp->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(tcp->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)tcp->reglist[sub], tcp->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
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

        /*end*/
        INFO("- TCP tcp%d INIT DONE -\n", id);

ret_init:
        return ret;
}
