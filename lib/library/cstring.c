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
#include "logger.h"


/**
 * definitions
 *
 */
#define zmalloc() \
        do { \
                s = malloc(pure_size + 3); \
                if (unlikely(!s)) { \
                        ERROR("malloc string space failed !!!\n"); \
                        goto ret_s; \
                } \
                memset(s, 0, pure_size + 3); \
        } while(0)


/**
 * hexdi2s - change int to hex string
 * @num: digital of int type
 *
 */
inline char *hexdi2s(int num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(int) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "0x%d", num);

ret_s:
        return s;
}


/**
 * hexdui2s - change unsigned int to hex string
 * @num: digital of unsigned int type
 *
 */
inline char *hexdui2s(unsigned int num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(unsigned int) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "0x%u", num);

ret_s:
        return s;
}


/**
 * hexdl2s - change long to hex string
 * @num: digital of long type
 *
 */
inline char *hexdl2s(long num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(long) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "0x%ld", num);

ret_s:
        return s;
}


/**
 * hexdul2s - change unsigned long to hex string
 * @num: digital of unsigned long type
 *
 */
inline char *hexdul2s(unsigned long num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(unsigned long) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "0x%lu", num);

ret_s:
        return s;
}


/**
 * hexdll2s - change long long to hex string
 * @num: digital of long long type
 *
 */
inline char *hexdll2s(long long num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(long long) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "0x%lld", num);

ret_s:
        return s;
}


/**
 * hexdull2s - change unsigned long long to hex string
 * @num: digital of unsigned long long type
 *
 */
inline char *hexdull2s(unsigned long long num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(unsigned long long) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "0x%llu", num);

ret_s:
        return s;
}


/**
 * decdi2s - change int to dec string
 * @num: digital of int type
 *
 */
inline char *decdi2s(int num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(int) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "%d", num);

ret_s:
        return s;
}


/**
 * decdui2s - change unsigned int to string
 * @num: digital of unsigned int type
 *
 */
inline char *decdui2s(unsigned int num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(unsigned int) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "%u", num);

ret_s:
        return s;
}


/**
 * decdl2s - change long to string
 * @num: digital of long type
 *
 */
inline char *decdl2s(long num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(long) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "%ld", num);

ret_s:
        return s;
}


/**
 * decdul2s - change unsigned long to string
 * @num: digital of unsigned long type
 *
 */
inline char *decdul2s(unsigned long num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(unsigned long) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "%lu", num);

ret_s:
        return s;
}


/**
 * decdll2s - change long long to string
 * @num: digital of long long type
 *
 */
inline char *decdll2s(long long num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(long long) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "%lld", num);

ret_s:
        return s;
}


/**
 * decdull2s - change unsigned long long to string
 * @num: digital of unsigned long long type
 *
 */
inline char *decdull2s(unsigned long long num)
{
        char *s = NULL;
        int pure_size = 0;

        pure_size = (sizeof(unsigned long long) * __CHAR_BIT__) / 4;
        zmalloc();
        sprintf(s, "%llu", num);

ret_s:
        return s;
}
