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
#ifndef __COMMON_H__
#define __COMMON_H__
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This file defines all kernel structures.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "type.h"
#include "config.h"
#include "library.h"


/* * * * * * * * * * * * * * * * * * * * * * * *
 * struct declare
 * * * * * * * * * * * * * * * * * * * * * * * */
/*state machine*/
enum state {
        OFF = 0,     //off
        INIT,        //init
        RUN,         //run
        IDLE,        //idle
        SLEEP,       //sleep
        WAKEUP,      //wakeup
        READ,        //read
        WRITE,       //write
        CAL,         //calculate
        INPUT,       //input
        OUTPUT,      //output
};

/*ip register*/
typedef struct registers {
        char name[64];           //register name
        address32_t address;     //register address
        reg32_t value;           //register value
}regs;

/*ip operation*/
typedef struct device_ops {
        void (*poweron)();       //poweron
        void (*poweroff)();      //poweroff
        void (*idle)();          //idle
        void (*sleep)();         //sleep
        void (*wakeup)();        //wakeup
        int  (*init)();          //init
        void (*deinit)();        //deinit
        void (*read)();          //read
        void (*write)();         //write
        void (*setreg)();        //set register
        void (*getreg)();        //get register
        void (*clearreg)();      //clear register
        void (*tickarrive)();    //clock trigger
        void (*dump)();          //debug
}ip_operations;

/*ip*/
typedef struct device {
        char name[64];           //name
        int id;                  //id
        enum state status;       //state machine
        address32_t address;     //address: first reg-addr or mem-addr

        const ip_operations *ops;//operation

        address32_t **memory;    //memory space

        regs **reglist;          //register list
        hashtable *name2reg;     //register hashtable1: name->reg
        hashtable *addr2reg;     //register hashtable2: addr->reg

        struct device *parent;   //parent
        //FIXME: more? less?
        struct device *east;     //east connected ip
        struct device *west;     //west connected ip
        struct device *sourth;   //sourth connected ip
        struct device *north;    //north connected ip

        struct device **subips;  //submodule
        hashtable *name2subip;   //submodule hashtable1: name->subip
        hashtable *addr2subip;   //submodule hashtable2: addr->subip
}ip;

/*parameter*/
typedef struct parameter {
        int boardlink_count;
        int board_count;
        int chiplink_count;
        int chip_count;
        int ddr_count;
        int fifobuf_count;
        int pcie_count;
        int maincpu_count;
        int noc_count;
        int core_count;
        int ram_count;
        int ram_size;
        int reg_count;
        //FIXME: add more
}param;

/*simulator*/
typedef struct simulator {
        param *params;
        ip *product;
}simu;



/* * * * * * * * * * * * * * * * * * * * * * * *
 * function declare
 * * * * * * * * * * * * * * * * * * * * * * * */
/*power*/
int power_on(ip *product);
int power_off(ip *product);
int power_idle(ip *product);
int power_sleep(ip *product);

/*clock*/
int clock_run(ip *product);

/*product*/
int product_init(ip *father, ip *product, int id, param *params);
int product_run(ip *product);

/*boardlink*/
int boardlink_init(ip *father, ip *product, int id, param *params);

/*board*/
int board_init(ip *father, ip *board, int id, param *params);

/*chiplink*/
int chiplink_init(ip *father, ip *board, int id, param *params);

/*chip*/
int chip_init(ip *father, ip *board, int id, param *params);

/*core*/
int core_init(ip *father, ip *board, int id, param *params);



/* * * * * * * * * * * * * * * * * * * * * * * *
 * global variants declare
 * * * * * * * * * * * * * * * * * * * * * * * */
extern enum state global_state;  //the whole product run state-machine
extern u64 tick_counter;         //the tick counts from the beginning
extern int all_phase_done;       //all phase process ok


#endif
