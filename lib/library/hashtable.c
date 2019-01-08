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
#include <stdlib.h>
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
 * @string: a sring of charactors
 *
 */
static int gen_hashkey(const char *string)
{
        int hashkey = -1;
        size_t slength = 0;
        const char* s = string;

        /*check params*/
        if (unlikely(!s))
                goto ret_hashkey;

        /*begin*/
        hashkey = 0;
        slength = strlen(s);

        while (slength--)
                hashkey += *s++;

ret_hashkey:
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
 * hashrandom - get new hashkey by random compute the old hashid and hashkey
 * @hashkey: old hashkey
 * @hashid: old hashid
 *
 */
static inline int hashrandom(int hashkey, int hashid)
{
        return (hashid + hashkey%10 + 1);
}


/**
 * hashcore - hash an element to hashtable
 * @string: a sring of charactors
 * @table: pointer to hashtable
 *
 */
int hashcore(const char *string, hashtable *table)
{
        int hashkey = -1;
        int hashid = -1;
        int count = 0;

        /*check params*/
        if (unlikely(!string || !table)) {
                printf("string or hashtable is NULL! %s,%s,%d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_hashid;
        }

        /*being*/
        hashkey = gen_hashkey(string);
        if (unlikely(-1 == hashkey)) {
                printf("generate hashkey fail! %s,%s,%d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_hashid;
        }

        hashid = hashfunc(hashkey);

        /*FIXME:avoid hashkey == 0*/
        if (unlikely(!hashkey))
                goto do_rehash_core;

        /*NULL means empty, got place!*/
        if (likely(!(table[hashid].element))) {
                table[hashid].hashkey = hashkey;
                table[hashid].string = string;
                goto ret_hashid;
        }

do_rehash_core:
        /*rehash: pseudo random detect to resovle conflicts*/
        do {
                count++;

                hashkey = hashrandom(hashkey, hashid);
                hashid = hashfunc(hashkey);

                /*FIXME:avoid hashkey == 0*/
                if (unlikely(!hashkey))
                        continue;
        } while (table[hashid].element);

        table[hashid].hashkey = hashkey;
        table[hashid].string = string;


        printf("DEBUG: hash conflicts count %d, IN %s,%s,%d\n",
                        count, __FILE__, __func__, __LINE__);

ret_hashid:
        return hashid;
}


/**
 * findelement - find the element hashed
 * @string: a sring of charactors
 * @table: pointer to hashtable
 *
 */
void * findelement(const char *string, hashtable *table)
{
        void *element = NULL;
        int hashkey = -1;
        int hashid = -1;
        int count = 0;

        if (unlikely(!string || !table)) {
                printf("string or hashtable is NULL! %s,%s,%d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_element;
        }

        /*begin*/
        hashkey = gen_hashkey(string);
        if (unlikely(-1 == hashkey)) {
                printf("generate hashkey fail! %s,%s,%d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_element;
        }

        hashid = hashfunc(hashkey);
        element = table[hashid].element;
        /*NULL means empty, miss!*/
        if (unlikely(!element)) {
                printf("MISS: element %s not hashed in table %p\n",
                                string, table);
                goto ret_element;
        }

        /*FIXME:avoid hashkey == 0*/
        if (unlikely(!hashkey))
                goto do_rehash_find;

        /*got element*/
        if (likely(hashkey == table[hashid].hashkey) &&
                        likely(!strcmp(string, table[hashid].string))) {
                goto ret_element;
        }

do_rehash_find:
        /*resovle conflicts: rehash*/
        do {
                count++;

                hashkey = hashrandom(hashkey, hashid);
                hashid = hashfunc(hashkey);

                /*FIXME:avoid hashkey == 0*/
                if (unlikely(!hashkey))
                        continue;

                /*got*/
                if (likely(hashkey == table[hashid].hashkey) &&
                                likely(!strcmp(string, table[hashid].string))) {
                        element = table[hashid].element;

                        printf("DEBUG: hash conflicts count %d, IN %s,%s,%d\n",
                                        count, __FILE__, __func__, __LINE__);
                        goto ret_element;
                }

                /*hashkey conflicts, miss!*/
                element = NULL;
                printf("MISS: element %s not hashed in table %p\n", string, table);
        } while (table[hashid].element);


ret_element:
        return element;
}


/**
 * dump_hashtable - dump a hashtable
 * @table: pointer to hashtable
 *
 */
void dump_hashtable(hashtable *table)
{
        int hashid = -1;

        if (unlikely(!table)) {
                printf("hashtable is NULL! %s,%s,%d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*begin*/
        for (hashid = 0; hashid <= HASHTABLE_MAXID; hashid++) {
                printf("==========DUMP HASHTABLE %p BEGIN==========\n", table);

                table[hashid].string = (!table[hashid].string) ?
                        ("NULL") : (table[hashid].string);

                printf("hashid=%d, hashkey=%d, hashstring=%s, hashelement=%p\n",
                                hashid, table[hashid].hashkey,
                                table[hashid].string, table[hashid].element);

                printf("==========DUMP HASHTABLE %p END============\n", table);
        }

ret_dump:
        return;
}


/**
 * init_hashtable - init a hashtable
 *
 */
hashtable * init_hashtable()
{
        hashtable *table = NULL;

        /*begin*/
        table = (hashtable *)malloc(HASHTABLE_MAXID * sizeof(hashtable));
        if (unlikely(!table)) {
                printf("hashtable init failed: malloc error! %s,%s,%d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        memset((void *)table, 0, HASHTABLE_MAXID * sizeof(hashtable));

ret_init:
        return table;
}


/**
 * del_hashtable - delete a hashtable
 * @table: pointer to hashtable
 *
 */
int del_hashtable(hashtable *table)
{
        int delok = -1;
        int hashid = -1;

        if (unlikely(!table)) {
                printf("the hashtable is absent!!\n");
                goto ret_del;
        }

        /*begin*/
        for (hashid = 0; hashid <= HASHTABLE_MAXID; hashid++) {
                if (unlikely(!table[hashid].hashkey))
                        continue;

                table[hashid].hashkey = 0;
                table[hashid].string = NULL;
                table[hashid].element = NULL;
        }

        delok = 0;
        free(table);

ret_del:
        return delok;
}
