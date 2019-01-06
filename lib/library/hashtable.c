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
#include <string.h>
#include "type.h"
#include "cerr.h"
#include "compiler.h"
#include "library.h"


/**
 * Fibonacci Hash Magic Value
 *
 */
#define FIBONACCI_MAGIC16 0x9E37 //40503
#define FIBONACCI_MAGIC32 0x9E3779B9 //2654435769
#define FIBONACCI_MAGIC64 0x9E3779B97F4A7C15 //11400714819323198485
#define FIBONACCI_MAGIC FIBONACCI_MAGIC32 


/**
 * Hash Table ID Counts
 *
 */
#define HASHTABLE_COUNT_BIT 8
#define HASHTABLE_MAXID ((1 << HASHTABLE_COUNT_BIT) - 1) //255


/**
 * gen_hashkey - generate hashkey from a string
 * @sring: a sring of charactors
 *
 */
static int gen_hashkey(const char *string)
{
        int hashkey = -1;
        size_t slength = 0;
        const char* s = string;

        /*check params*/
        if (!s)
                goto ret;

        /*begin*/
        hashkey = 0;
        slength = strlen(s);

        while (slength--)
                hashkey += *s++;

ret:
        return hashkey;
}


/**
 * hashfunc - compute the hashid from the hashkey use Fibonacci Array
 * @hashkey: generated from a string
 *
 */
static inline int hashfunc(int hashkey)
{
        return ((hashkey * FIBONACCI_MAGIC) >> (32 - HASHTABLE_COUNT_BIT));
}


/**
 * hashcore - find the right place for the element
 * @element: hashtable element
 * @hashkey: the element's hash key
 * @hashtable: pointer to hashtable
 *
 */
static int hashcore(void *element, int hashkey, hashtable *table)
{
        int hashid = -1;

        /*check params*/
        if (!element || !table)
                goto ret;

        /*being*/
        hashid = hashfunc(hashkey);

        if (!(table[hashid]->element)) //NULL means empty
                goto ret;

        do {
                /*rehash: pseudo random detect to resovle conflicts*/
                hashkey = hashid + hashkey%10 + 1;
                hashid = hashfunc(hashkey);
        } while (table[hashid]->element);

ret:
        return hashid;
}
