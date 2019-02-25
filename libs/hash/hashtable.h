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
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This file defines all hashtable functions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "cerr.h"


/* hashtable struct*/
typedef struct hash_table hashtable;

/* hashtable functions*/
int insert_hashtable(const char *string, void *element, hashtable *table);
hashtable * init_hashtable();
void * lookfor_hashtable(const char *string, hashtable *table);
void dump_hashtable(hashtable *table);
int del_hashtable(hashtable *table);


#endif
