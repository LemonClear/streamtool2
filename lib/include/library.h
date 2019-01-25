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
#ifndef __LIBRARY_H__
#define __LIBRARY_H__
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This file defines all library functions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "cerr.h"
#include "compiler.h"


/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({                              \
        void *__mptr = (void *)(ptr);                                   \
        BUILD_BUG_ON_MSG(!__same_type(*(ptr), ((type *)0)->member) &&   \
                        ┊!__same_type(*(ptr), void),                    \
                        ┊"pointer type mismatch in container_of()");    \
        ((type *)(__mptr - offsetof(type, member))); })


/**
 * container_of_safe - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 * If IS_ERR_OR_NULL(ptr), ptr is returned unchanged.
 */
#define container_of_safe(ptr, type, member) ({                         \
        void *__mptr = (void *)(ptr);                                   \
        BUILD_BUG_ON_MSG(!__same_type(*(ptr), ((type *)0)->member) &&   \
                        ┊!__same_type(*(ptr), void),                    \
                        ┊"pointer type mismatch in container_of()");    \
        IS_ERR_OR_NULL(__mptr) ? ERR_CAST(__mptr) :                     \
                ((type *)(__mptr - offsetof(type, member))); })


/* hashtable struct*/
typedef struct hash_table {
        int hashkey;
        const char *string;
        void *element;
}hashtable;


/* hashtable functions*/
int insert_hashtable(const char *string, void *element, hashtable *table);
hashtable * init_hashtable();
void * lookfor_hashtable(const char *string, hashtable *table);
void dump_hashtable(hashtable *table);
int del_hashtable(hashtable *table);


/*cstring functions*/
char *hexdi2s(int num);
char *hexdui2s(unsigned int num);
char *hexdl2s(long num);
char *hexdul2s(unsigned long num);
char *hexdll2s(long long num);
char *hexdull2s(unsigned long long num);

char *decdi2s(int num);
char *decdui2s(unsigned int num);
char *decdl2s(long num);
char *decdul2s(unsigned long num);
char *decdll2s(long long num);
char *decdull2s(unsigned long long num);


#endif
