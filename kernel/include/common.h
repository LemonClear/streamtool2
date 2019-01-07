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


enum state {
        IDLE,    //idle
        INIT,    //init
        RUN,     //run
        READ,    //read
        WRITE,   //write
        CAL,     //calculate
        INPUT,   //input
        OUTPUT,  //output
};

/*ip register*/
typedef struct registers {
        const char* name;        //register name
        address_t addr;          //register address
        reg32_t value;           //register value
}regs;

/*ip operation*/
typedef struct device_ops {
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
        const char* name;        //ip name
        int id;                  //ip id
        ip_operations ops;       //ip operation
        struct regs **reglist;   //ip register list
        address32_t *address;    //ip memory space
        hashtable *name2reg;     //ip register hashtable1: name<->reg
        hashtable *addr2reg;     //ip register hashtable2: addr<->reg
        enum state status;       //ip state machine
        struct ip *parent;       //ip parent
        struct ip **subips;      //ip submodule
        hashtable *name2subip;   //ip submodule hashtable1: name<->reg
        hashtable *addr2subip;   //ip submodule hashtable2: addr<->reg
}ip;

/**/



#endif
