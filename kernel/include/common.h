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
        const char *name;        //register name
        address_t address;       //register address
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
        void (*set_reg)();       //set register
        void (*get_reg)();       //get register
        void (*clear_reg)();     //clear register
        void (*tick_arrive)();   //clock trigger
        void (*dump)();          //debug
}ip_operations;

/*ip*/
typedef struct device {
        const char *name;        //ip name
        int id;                  //ip id
        enum state status;       //ip state machine
        address32_t address;     //ip address: first reg-addr or mem-addr

        ip_operations *ops;      //ip operation

        address32_t **memory;    //ip memory space

        regs **reglist;          //ip register list
        hashtable *name2reg;     //ip register hashtable1: name->reg
        hashtable *addr2reg;     //ip register hashtable2: addr->reg

        struct ip *parent;       //ip parent
        //FIXME: more? less?
        struct ip *east;         //ip east connected ip
        struct ip *west;         //ip west connected ip
        struct ip *sourth;       //ip sourth connected ip
        struct ip *north;        //ip north connected ip

        struct ip **subips;      //ip submodule
        hashtable *name2subip;   //ip submodule hashtable1: name->subip
        hashtable *addr2subip;   //ip submodule hashtable2: addr->subip
}ip;

/*parameter*/
typedef struct parameter {
        int board_count;
        int boardlink_count;
        int chip_count;
        int chiplink_count;
        int core_count;
        int noc_count;
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
int product_init(ip *product, param *params);
int product_run(ip *product);

/*board*/
int board_init(ip *product, param *params);


/* * * * * * * * * * * * * * * * * * * * * * * *
 * global variants declare
 * * * * * * * * * * * * * * * * * * * * * * * */
extern enum state global_state;  //the whole product run state-machine
extern u64 tick_counter;         //the tick counts from the beginning
extern int all_phase_done;       //all phase process ok


#endif
