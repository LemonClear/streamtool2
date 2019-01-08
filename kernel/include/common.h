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
        void (*init)();          //init
        void (*deinit)();        //deinit
        void (*read)();          //read
        void (*write)();         //write
        void (*set_reg)();       //set register
        void (*get_reg)();       //get register
        void (*clear_reg)();     //clear register
        void (*cicle_arrive)();  //clock trigger
        void (*dump)();          //debug
}ip_operations;

/*ip structure*/
typedef struct device {
        const char *name;        //ip name
        int id;                  //ip id
        enum state status;       //ip state machine
        address32_t address;     //ip address: first reg-addr or mem-addr

        ip_operations ops;       //ip operation

        address32_t **memory;    //ip memory space

        regs **reglist;   //ip register list
        hashtable *name2reg;     //ip register hashtable1: name->reg
        hashtable *addr2reg;     //ip register hashtable2: addr->reg

        struct ip *parent;       //ip parent

        struct ip **subips;      //ip submodule
        hashtable *name2subip;   //ip submodule hashtable1: name->subip
        hashtable *addr2subip;   //ip submodule hashtable2: addr->subip
}ip;

/*parameters*/
typedef struct parameter {
        int id;
        //FIXME: add more
}param;


/*power: function definitions*/
int poweron(ip *product);
int poweroff(ip *product);
int poweridle(ip *product);
int powersleep(ip *product);
int powerrun(ip *product);

/*product: function definitions*/
int product_init(ip *product, param *params);


#endif
