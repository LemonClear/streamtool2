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
 * __on - board power on
 * @board:   board pointer
 *
 */
static int __on(ip *board)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!board)) {
                ERROR("board is null !!!\n");
                goto ret_on;
        }

        /*begin*/
        INFO("- BOARD %s POWER ON GO>>> -\n", board->name);

        /*board level do 1st*/
        //FIXME: todo...

        /*board have no subip*/
        if (unlikely(!board->subips)) {
                ERROR("board->subips is null !!!\n");
                goto ret_on;
        }

        /*power on subips 2nd*/
        while (board->subips[id]) {
                /*each subip*/
                ret = board->subips[id]->ops->poweron(board->subips[id]);
                if (unlikely(ret)) {
                        ERROR("power on subip%d-%s failed !!!\n",
                                        id, board->subips[id]->name);
                        goto ret_on;
                }
                /*next subip*/
                id++;
        }

        /*change state machine 3rd*/
        board->status = RUN;

        /*end*/
        INFO("- BOARD %s POWER ON DONE -\n", board->name);

ret_on:
        return ret;
}


/**
 * __off - board power off
 * @board:   board pointer
 *
 */
static int __off(ip *board)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!board)) {
                ERROR("board is null !!!\n");
                goto ret_off;
        }

        /*begin*/
        INFO("- BOARD %s POWER OFF GO>>> -\n", board->name);

        /*board have no subip*/
        if (unlikely(!board->subips)) {
                ERROR("board->subips is null !!!\n");
                goto ret_off;
        }

        /*power off subips 1st*/
        while (board->subips[id]) {
                /*each subip*/
                ret = board->subips[id]->ops->poweroff(board->subips[id]);
                if (unlikely(ret)) {
                        ERROR("power off subip%d-%s failed !!!\n",
                                        id, board->subips[id]->name);
                        goto ret_off;
                }
                /*next subip*/
                id++;
        }

        /*board level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        board->status = OFF;

        /*end*/
        INFO("- BOARD %s POWER OFF DONE -\n", board->name);

ret_off:
        return ret;
}


/**
 * __idle - board idle
 * @board:   board pointer
 *
 */
static int __idle(ip *board)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!board)) {
                ERROR("board is null !!!\n");
                goto ret_idle;
        }

        /*begin*/
        INFO("- BOARD %s IDLE GO>>> -\n", board->name);

        /*board have no subip*/
        if (unlikely(!board->subips)) {
                ERROR("board->subips is null !!!\n");
                goto ret_idle;
        }

        /*idle subips 1st*/
        while (board->subips[id]) {
                /*each subip*/
                ret = board->subips[id]->ops->idle(board->subips[id]);
                if (unlikely(ret)) {
                        ERROR("idle subip%d-%s failed !!!\n",
                                        id, board->subips[id]->name);
                        goto ret_idle;
                }
                /*next subip*/
                id++;
        }

        /*board level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        board->status = IDLE;

        /*end*/
        INFO("- BOARD %s IDLE DONE -\n", board->name);

ret_idle:
        return ret;
}


/**
 * __sleep - board sleep
 * @board:   board pointer
 *
 */
static int __sleep(ip *board)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!board)) {
                ERROR("board is null !!!\n");
                goto ret_sleep;
        }

        /*begin*/
        INFO("- BOARD %s SLEEP GO>>> -\n", board->name);

        /*board have no subip*/
        if (unlikely(!board->subips)) {
                ERROR("board->subips is null !!!\n");
                goto ret_sleep;
        }

        /*sleep subips 1st*/
        while (board->subips[id]) {
                /*each subip*/
                ret = board->subips[id]->ops->sleep(board->subips[id]);
                if (unlikely(ret)) {
                        ERROR("sleep subip%d-%s failed !!!\n",
                                        id, board->subips[id]->name);
                        goto ret_sleep;
                }
                /*next subip*/
                id++;
        }

        /*board level do 2nd*/
        //FIXME: todo...

        /*change state machine 3rd*/
        board->status = SLEEP;

        /*end*/
        INFO("- BOARD %s SLEEP DONE -\n", board->name);

ret_sleep:
        return ret;
}


/**
 * __wakeup - board wakeup
 * @board:  board pointer
 *
 */
static int __wakeup(ip *board)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!board)) {
                ERROR("board is null !!!\n");
                goto ret_wakeup;
        }

        /*begin*/
        INFO("- BOARD %s WAKEUP GO>>> -\n", board->name);

        /*board level do 1st*/
        //FIXME: todo...

        /*board have no subip*/
        if (unlikely(!board->subips)) {
                ERROR("board->subips is null !!!\n");
                goto ret_wakeup;
        }

        /*wakeup subips 2nd*/
        while (board->subips[id]) {
                /*each subip*/
                ret = board->subips[id]->ops->wakeup(board->subips[id]);
                if (unlikely(ret)) {
                        ERROR("wakeup subip%d-%s failed !!!\n",
                                        id, board->subips[id]->name);
                        goto ret_wakeup;
                }
                /*next subip*/
                id++;
        }

        /*change state machine 3rd*/
        board->status = RUN;

        /*end*/
        INFO("- BOARD %s WAKEUP DONE -\n", board->name);

ret_wakeup:
        return ret;
}


/**
 * __tick - one tick trigger
 * @board:   self pointer
 *
 */
static int __tick(ip *board)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!board)) {
                ERROR("board is null !!!\n");
                goto ret_tick;
        }

        /*begin*/
        INFO("- BOARD %s TICK %llu GO>>> -\n",
                        board->name, tick_counter);

        /*board level do 1st*/
        //FIXME: todo...

        /*board have no subip*/
        if (unlikely(!board->subips)) {
                ERROR("board->subips is null !!!\n");
                goto ret_tick;
        }

        /*tick trigger subips 2nd*/
        while (board->subips[id]) {
                /*each subip*/
                ret = board->subips[id]->ops->tickarrive(board->subips[id]);
                if (unlikely(ret)) {
                        ERROR("wakeup subip%d-%s failed !!!\n",
                                        id, board->subips[id]->name);
                        goto ret_tick;
                }
                /*next subip*/
                id++;
        }

        /*end*/
        INFO("- BOARD %s TICK %llu DONE -\n",
                        board->name, tick_counter);

ret_tick:
        return ret;
}


/**
 * __dump - board dump informations
 * @board:   board pointer
 *
 */
static int __dump(ip *board)
{
        int ret = -1;
        int id = 0;

        if (unlikely(!board)) {
                ERROR("board is null !!!\n");
                goto ret_dump;
        }

        /*begin*/
        DEBUG("--- DUMP BOARD %s BEGIN ---\n", board->name);

        /*dump board elements 1st*/
        //FIXME: todo...

        /*board have no subip*/
        if (unlikely(!board->subips)) {
                ERROR("board->subips is null !!!\n");
                goto ret_dump;
        }

        /*dump subips 2nd*/
        while (board->subips[id]) {
                /*each subip*/
                ret = board->subips[id]->ops->dump(board->subips[id]);
                if (unlikely(ret)) {
                        ERROR("dump subip%d-%s failed !!!\n",
                                        id, board->subips[id]->name);
                        goto ret_dump;
                }
                /*next subip*/
                id++;
        }

        /*end*/
        DEBUG("--- DUMP BOARD %s END ---\n", board->name);

ret_dump:
        return ret;
}
/**
 * ops structure
 *
 */
static const ip_operations board_ops = {
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
 */
static int parse_regconfig(regs **reglist)
{
        int ret = -1;
        char *regconfig = "./configs/regconfig.board";
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
 * board_alloc - alloc board elements
 * @board:     pointer to board
 * @params:    init parameters
 *
 */
static int board_alloc(ip *board, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //NO need on board level!!!

        /*reg list*/
        if (unlikely(!params->board_reg_count)) {
                WARNING("have no register !!!\n");
        }

        //Trick: malloc(0)!=NULL
        board->reglist = malloc((params->board_reg_count + 1) * sizeof(regs *));
        if (unlikely(!board->reglist)) {
                ERROR("alloc reglist failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)board->reglist, 0, (params->board_reg_count + 1) * sizeof(regs *));

        for (id = 0; id < params->board_reg_count; id++) {
                board->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!board->reglist[id])) {
                        ERROR("alloc reg%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)board->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        board->name2reg = init_hashtable();
        if (unlikely(!board->name2reg)) {
                ERROR("alloc hashtable name2reg failed !!!\n");
                goto ret_alloc;
        }

        board->addr2reg = init_hashtable();
        if (unlikely(!board->addr2reg)) {
                ERROR("alloc hashtable addr2reg failed !!!\n");
                goto ret_alloc;
        }

        /*subips list*/
        board->subips = malloc((params->chip_count +
                                params->chiplink_count + params->ddr_count +
                                params->fifo_count + params->pcie_count +
                                params->maincpu_count + 1) * sizeof(ip *));
        if (unlikely(!board->subips)) {
                ERROR("alloc subip array failed !!!\n");
                goto ret_alloc;
        }
        memset((void *)board->subips, 0, (params->chip_count +
                                params->chiplink_count + params->ddr_count +
                                params->fifo_count + params->pcie_count +
                                params->maincpu_count + 1) * sizeof(ip *));

        for (id = 0; id < (params->chip_count +
                                params->chiplink_count + params->ddr_count +
                                params->fifo_count + params->pcie_count +
                                params->maincpu_count); id++) {
                board->subips[id] = malloc(sizeof(ip));
                if (unlikely(!board->subips[id])) {
                        ERROR("alloc subip%d failed !!!\n", id);
                        goto ret_alloc;
                }
                memset((void *)board->subips[id], 0, sizeof(ip));
        }

        /*subips hastable*/
        board->name2subip = init_hashtable();
        if (unlikely(!board->name2subip)) {
                ERROR("alloc hashtable name2subip failed !!!\n");
                goto ret_alloc;
        }

        board->addr2subip = init_hashtable();
        if (unlikely(!board->addr2subip)) {
                ERROR("alloc hashtable addr2subip failed !!!\n");
                goto ret_alloc;
        }

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * board_init - init board with params
 * @father:    pointer to the board belongs to
 * @board:     pointer to board
 * @id:        board id
 * @params:    init parameters
 *
 */
int board_init(ip *father, ip *board, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char *addr2str = NULL;

        /*begin*/
        INFO("- BOARD board%d INIT GO>>> -\n", id);

        if (unlikely(!board) || unlikely(!params)) {
                ERROR("board is %p, params is %p !!!\n", board, params);
                goto ret_init;
        }

        /*alloc*/
        ret = board_alloc(board, params);
        if (unlikely(ret)) {
                ERROR("board alloc elements failed !!!\n");
                goto ret_init;
        }

        /*name*/
        sprintf(board->name, "board%d", id);

        /*id*/
        board->id = id;

        /*state machine*/
        board->status = OFF;

        /*ops*/
        board->ops = &board_ops;

        /*memory*/
        //NO need on board level!!!

        /*reg list*/
        ret = parse_regconfig(board->reglist);
        if (unlikely(ret)) {
                ERROR("board reglist init failed !!!\n");
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->board_reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(board->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(board->reglist[sub]->name,
                                (void *)board->reglist[sub],
                                board->name2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2reg failed !!!\n",
                                        board->reglist[sub]->name);
                        goto ret_init;
                }

                /*table addr2reg*/
                addr2str = hexdui2s(board->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)board->reglist[sub], board->addr2reg);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2reg failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*address*/
        //FIXME: according to reality
        board->address = board->reglist;

        /*parent*/
        board->parent = father;

        /*connected*/
        //No connected

        /*subips: chip 1st*/
        for (sub = 0; sub < params->chip_count; sub++) {
                /*call subip:chip init function*/
                ret = chip_init(board, board->subips[sub], sub, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-chip init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: chiplink 2nd*/
        for (; sub < (params->chip_count + params->chiplink_count); sub++) {
                /*call subip:chiplink init function*/
                ret = chiplink_init(board, board->subips[sub],
                                sub - params->chip_count, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-chiplink init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: ddr 3rd*/
        for (; sub < (params->chip_count + params->chiplink_count +
                                params->ddr_count); sub++) {
                /*call subip:ddr init function*/
                ret = ddr_init(board, board->subips[sub],
                                sub - params->chip_count - params->chiplink_count, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-ddr init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: fifo 4th*/
        for (; sub < (params->chip_count + params->chiplink_count +
                                params->ddr_count + params->fifo_count); sub++) {
                /*call subip:fifo init function*/
                ret = fifo_init(board, board->subips[sub],
                                sub - params->chip_count - params->chiplink_count -
                                params->ddr_count, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-fifo init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: pcie 5th*/
        for (; sub < (params->chip_count + params->chiplink_count +
                                params->ddr_count + params->fifo_count +
                                params->pcie_count); sub++) {
                /*call subip:pcie init function*/
                ret = pcie_init(board, board->subips[sub],
                                sub - params->chip_count - params->chiplink_count -
                                params->ddr_count - params->fifo_count, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-pcie init failed !!!\n", sub);
                        goto ret_init;
                }
        }
        /*subips: maincpu 6th*/
        for (; sub < (params->chip_count + params->chiplink_count +
                                params->ddr_count + params->fifo_count +
                                params->pcie_count + params->maincpu_count); sub++) {
                /*call subip:maincpu init function*/
                ret = maincpu_init(board, board->subips[sub],
                                sub - params->chip_count - params->chiplink_count -
                                params->ddr_count - params->fifo_count -
                                params->pcie_count, params);
                if (unlikely(ret)) {
                        ERROR("subip%d-maincpu init failed !!!\n", sub);
                        goto ret_init;
                }
        }

        /*subips: hashtable*/
        for (sub = 0; sub < (params->chip_count +
                                params->chiplink_count + params->ddr_count +
                                params->fifo_count + params->pcie_count +
                                params->maincpu_count); sub++) {
                /*bypass empty subip elements*/
                if (unlikely(!strcmp(board->subips[sub]->name, "")))
                        continue;

                /*table name2subip*/
                ret = insert_hashtable(board->subips[sub]->name,
                                (void *)board->subips[sub],
                                board->name2subip);
                if (unlikely(ret)) {
                        ERROR("hash %s to name2subip failed !!!\n",
                                        board->subips[sub]->name);
                        goto ret_init;
                }

                /*table addr2subip*/
                addr2str = hexdui2s(board->subips[sub]->address);
                ret = insert_hashtable(addr2str, (void *)board->subips[sub],
                                board->addr2subip);
                if (unlikely(ret)) {
                        ERROR("hash %s to addr2subip failed !!!\n", addr2str);
                        goto ret_init;
                }
        }

        /*end*/
        INFO("- BOARD board%d INIT DONE -\n", id);

ret_init:
        return ret;
}
